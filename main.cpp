#include <systemc.h>

// HelloWorld模块
SC_MODULE(HelloWorld) {
    SC_CTOR(HelloWorld) {
        // 在构造函数中输出Hello World!
        cout << "Hello World!" << endl;
    }
};

// 主函数
int sc_main(int argc, char* argv[]) {
    // 创建HelloWorld实例
    HelloWorld hello("hello");

    // 运行仿真
    sc_start();

    return 0;
}
