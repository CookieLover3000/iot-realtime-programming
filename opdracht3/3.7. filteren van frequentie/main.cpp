/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <arm_math.h>
#include "Kernel.h"
#include "Semaphore.h"
#include "ThisThread.h"
#include "cmsis_os.h"
#include "mbed.h"
#include "dsp.h"

// Blinking rate in milliseconds
#define KNIPPER_Tijd   1000ms
#define M_PI 3.14159265359
#define FFT_SIZE 256  
using ThisThread::sleep_for;


AnalogIn ain(A0);

Thread thread,thrSin,thrAnalog;
float buf[256];

float samples[FFT_SIZE * 2];
float samples2[FFT_SIZE * 2];
float freqDomain[FFT_SIZE];
float freqDomain2[FFT_SIZE];
float timeDomain[FFT_SIZE];
float signaal1rij[FFT_SIZE];
float signaal2rij[FFT_SIZE];

const unsigned int gr=255;

Queue<float, FFT_SIZE> queue1, queue2;
MemoryPool<float, FFT_SIZE> mpool1, mpool2;

Semaphore sem(0);

void maakSignaal() {
    int i = 0;
    while(true) {
        float k= i*(2*M_PI)/gr;

        float signaal1 = sin(4 *k);
        signaal1rij[i]=signaal1;
        float signaal2 = sin((ain.read_u16()/2000.0) *k);

        signaal2rij[i]=signaal2;
        float *optel = mpool1.try_alloc_for(Kernel::wait_for_u32_forever);

        *optel = signaal1 +signaal2;

        queue1.try_put_for(Kernel::wait_for_u32_forever, optel);

        buf[i]=*optel;
        samples[2*i]=*optel;
        samples[2*i+1] = 0.0;  
        timeDomain[i] = samples[2*i];

        i++;
        if(k >2*M_PI) {
            k=0;
            i=0;
        }
    }
}

void fft() {
    float samplesLocal[FFT_SIZE * 2];
    while(true) {

        for (int i=0; i<FFT_SIZE; i++) {
            float *value = nullptr;
            queue1.try_get_for(Kernel::wait_for_u32_forever, &value);
            samplesLocal[2*i] = *value;
            samplesLocal[2*i+1] = 0.0f;
            mpool1.free(value);
        }
        arm_cfft_radix4_instance_f32 fft_inst;
        arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
        arm_cfft_radix4_f32(&fft_inst, samplesLocal);
        arm_cmplx_mag_f32(samplesLocal, freqDomain, FFT_SIZE);

        for(int i = 0; i < FFT_SIZE;i++){
            float *freqValue = mpool2.try_alloc_for(Kernel::wait_for_u32_forever);
            *freqValue = freqDomain[i];
            queue2.try_put_for(Kernel::wait_for_u32_forever, freqValue);
        }
    }
}

void invFft() {
    float samplesLocal[FFT_SIZE * 2];
    while(1) {

        for (int i=0; i<FFT_SIZE; i++) {
            float *value = nullptr;
            queue2.try_get_for(Kernel::wait_for_u32_forever, &value);
            samplesLocal[2*i] = *value;
            samplesLocal[2*i+1] = 0.0f;
            mpool2.free(value);
        }
    
        for (int i=0; i<FFT_SIZE; i++) {
             if( i < 10 && (samplesLocal[i] > 1 || samplesLocal[i] < -1  ) ) {
                 samples2[i]=samples2[i-1];
             }
             else {
                 samples2[i]=samplesLocal[i];
            }
        }

        arm_cfft_radix4_instance_f32 fft_inst;
        arm_cmplx_mag_f32(samples2, freqDomain2, FFT_SIZE);     //absolute waarde van het freq domein na aanpassingen
        arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 1, 1);   //initialisatie voor de inverse FFT
        arm_cfft_radix4_f32(&fft_inst, samples2);

        sem.release();
    }
}

void printFft() {
    while(true) {
        sem.acquire();
        for (int i = 1; i < 127; i++) { // print only first half, the others are imaginary
            printf("%.3f\t%.3f\t%.3f\t", 3 + signaal1rij[i], 5 + signaal2rij[i],buf[i]);
            printf("%f\t%f\t",freqDomain[i],freqDomain2[i]);
            printf("%f\n",samples2[2 * i]);
        }
    }
}

void sinus()
{
    const unsigned int gr=255;
    unsigned i=0;
    while(true) {

        float k= i*(2*M_PI)/gr;
   
        float signaal1 = sin(4 *k);
        signaal1rij[i]=signaal1;
        float signaal2 = sin((ain.read_u16()/2000.0) *k);


        signaal2rij[i]=signaal2;
        float optel = signaal1 +signaal2;
       
        buf[i]=optel;
        samples[2*i]=optel;
        samples[2*i+1] = 0.0;  
        timeDomain[i] = samples[2*i];

        i++;
        if(k >2*M_PI) {
            k=0;i=0;
            arm_cfft_radix4_instance_f32 fft_inst;  
            arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
            arm_cfft_radix4_f32(&fft_inst, samples);
            arm_cmplx_mag_f32(samples, freqDomain, FFT_SIZE);
     

            for (int i=0; i<FFT_SIZE; i++) {
                 if( i < 10 && (samples[i] > 1 || samples[i] < -1  ) ) {
                     samples2[i]=samples2[i-1];
                 }
                 else {
                     samples2[i]=samples[i];
                }
            }

            arm_cmplx_mag_f32(samples2, freqDomain2, FFT_SIZE);     //absolute waarde van het freq domein na aanpassingen
            arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 1, 1);   //initialisatie voor de inverse FFT
            arm_cfft_radix4_f32(&fft_inst, samples2);
            printf("einde ronde\n");
            for (int i = 1; i < 127; i++) { // print only first half, the others are imaginary
                printf("%.3f\t%.3f\t%.3f\t", 3 + signaal1rij[i], 5 + signaal2rij[i],buf[i]);
                printf("%f\t%f\t",freqDomain[i],freqDomain2[i]);
                printf("%f\n",samples2[2 * i]);
            }
        }  
    }
}    

void analog()
{
    printf("in thread analog\n");
    while(true) {
        printf("%d\n",ain.read_u16());           
        sleep_for(100ms);

    }

}



int main()
{
    DigitalOut led1(D6);
    // printf("Hoi2\n");

    Thread thrSignaal, thrFFT, thrInvFFT, thrPrint;
    thrSignaal.start(maakSignaal);
    thrFFT.start(fft);
    thrInvFFT.start(invFft);
    thrPrint.start(printFft);
    // thrSin.start(sinus);


    while (true) {
        led1 = !led1;
        ThisThread::sleep_for(KNIPPER_Tijd);
    }
}
