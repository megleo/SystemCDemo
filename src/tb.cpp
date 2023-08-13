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
        start_time[i] = sc_time_stamp();
        do
        {
            wait();
        } while (!inp_rdy.read());
        inp_val.write(0);
    }
    
    // simulation hanging gard
    wait(10000);
    printf("Hanging simulation stoped by TB Source thread. \n");
    sc_stop();
}

void tb::sink() {
    sc_int<16> indata;
    sc_clock *clk_p = dynamic_cast<sc_clock*>(clk.get_interface());
    clock_period = clk_p->period();
    std::cout << "clock_period " << clock_period.to_double() << std::endl;
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
        double cha = (end_time[i] - start_time[i]).to_double();
        double latencyPeriod  = cha / clock_period.to_double();
        total_circle += latencyPeriod;
        outp_rdy.write(0);
        fprintf(outfp, "%d\t%f\n", indata.to_int(), latencyPeriod);
        cout << i << ":\t" << indata.to_double() << "\t: latency time: " << latencyPeriod << endl;
    }

    double total_throughput = (start_time[63] - start_time[0]).to_double() / clock_period.to_double();
    cout << "Total latency time:\t" << total_circle << endl;
    fprintf(outfp, "Total latency time:\t%f", total_circle);
    fprintf(outfp, "Average throughput is %f cycles per input.", total_throughput / 63);
    cout << "Average throughput is " << total_throughput / 63 << " cycles per input." << std::endl;
    fclose(outfp);
    sc_stop();
}