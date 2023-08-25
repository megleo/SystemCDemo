#include <systemc.h>
template<typename DT>
SC_MODULE(and2){
    sc_in<DT> a;
    sc_in<DT> b;
    sc_out<DT> f;
    // sc_in<bool> clk;

    void func() {
        cout << "a = " << a <<endl;
        cout << "b = " << b <<endl;
        f.write(a.read() + b.read());
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
    sc_signal<sc_uint<2>> a;
    sc_signal<sc_uint<2>> b;
    sc_signal<sc_uint<2>> f;

    // 创建模块并连接信号
    and2<sc_uint<2>> addG("andGate");
    addG.a(a);
    addG.b(b);
    addG.f(f);

    a = *argv[1];
    b = *argv[2];
            cout << "a = " << a <<endl;
        cout << "b = " << b <<endl;
    sc_start();
    cout << "f = " << f << endl;
    return 0;
}