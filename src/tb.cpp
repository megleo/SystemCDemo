#include "tb.h"

void tb::source() {
    // Reset
    inp.write(0);
    inp_val.write(0);
    rst.write(1);
    wait();
    rst.write(0);
    wait();
    sc_int<16> tmp;

    for (size_t i = 0; i < 64; i++)
    {
        if (i > 23 && i < 29)
        {
            tmp = 256;
        }else{
            tmp = 0;
        }
        
        inp_val.write(1);
        inp.write(tmp);

        do
        {
            wait();
        } while (!inp_rdy.read());
        inp_val.write(0);
        start_time[i] = sc_time_stamp();
    }
    
    // simulation hanging gard
    wait(10000);
    printf("Hanging simulation stoped by TB Source thread. \n");
    sc_stop();
}

void tb::sink() {
    sc_int<16> indata;
    // Extact clock period
    // Open simulation output results file
    char output_file[256];
    sprintf(output_file, "./output.dat");
    outfp = fopen(output_file, "wb");

    if(outfp == NULL) {
        printf("Could not open output.dat for waitting.\n");
        exit(0);
    }

    // Initialize port
    outp_rdy.write(0);
    double total_circle = 0;

    // Read output comming from DUT
    for (size_t i = 0; i < 64; i++)
    {
        outp_rdy.write(1);
        do
        {
            wait();
        } while (!outp_val.read());
        indata = outp.read();
        end_time[i] = sc_time_stamp();
        outp_rdy.write(0);
        fprintf(outfp, "%d\n", indata.to_int());
        cout << i << ":\t" << indata.to_double() << endl;
    }
    sc_stop();
}