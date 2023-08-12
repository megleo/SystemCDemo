#include <systemc.h>
template<typename DT>
SC_MODULE(and2){
    sc_in<DT> a;
    sc_in<DT> b;
    sc_out<DT> f;
    // sc_in<bool> clk;

    void func() {
        f.write(a.read() & b.read());
    }

    SC_CTOR(and2) {
        SC_METHOD(func);
        sensitive << a << b;
        // sensitive << clk.pos();
        // sensitive << clk.neg();

    }
};

int sc_main(int argc, char* argv[]) {
    // 创建信号
    sc_signal<sc_uint<1>> a;
    sc_signal<sc_uint<1>> b;
    sc_signal<sc_uint<1>> f;

    // 创建模块并连接信号
    and2<sc_uint<1>> addG("andGate");
    addG.a(a);
    addG.b(b);
    addG.f(f);

    a = 1;
    b = 1;
    sc_start();
    cout << "f = " << f << endl;
    return 0;
}