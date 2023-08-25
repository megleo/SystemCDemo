#include <systemc.h>

SC_MODULE(fir) {
    sc_in< bool >               clk;
    sc_in <bool >               rst;

    sc_in< sc_int<16> >        inp;
    sc_in< bool >               inp_vld;
    sc_out<bool>                inp_rdy;

    sc_out< sc_int<16> >       outp;
    sc_out< bool >              outp_vld;
    sc_in <bool>                outp_rdy;

    void fir_main();
    // Coefficients for each FIR

    SC_CTOR(fir) {
        // 两个参数,一个是线程的函数,一个是时钟的边沿(这里是上升沿) 这个process sensitivie to.
        SC_CTHREAD(fir_main, clk.pos() );
        // 用于指定一个复位信号rst，并将其设置为真（true）。这表示在rst为真（高电平）时，线程会被复位。
        reset_signal_is(rst, true);
    }
};