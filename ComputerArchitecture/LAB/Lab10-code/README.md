文件目录及说明：

```
.
├── README.md
├── coe - 汇编和coe文件
│   ├── README.md
│   ├── lab10.asm
│   ├── lab10.coe
│   ├── lab10_all.asm
│   └── lab10_all.coe
├── constrs
│   └── nexys_a7.xdc  - 引脚约束文件，用于综合和上板，需要添加到工程中
├── ip - ip核约束文件，添加到工程生成ip core
│   ├── Ram.xci
│   └── Rom.xci
├── src - 需要加入到工程的中的源文件
│   ├── AluOp.vh
│   ├── Control.edf   - 用于综合，不能仿真
│   ├── Control.v     - 用于综合，不能仿真
│   ├── Control_sim.v - 用于仿真，不能综合
│   ├── Core.v        - 需要添加代码，里面有TODO说明
│   ├── IO_Manager.sv - 一般不要修改
│   ├── SCPU.v        - 包含Control的接口说明，以及Datapath的接口
│   └── Top.sv        - 添加Registers的输出时需要修改
└── test_bench
    └── Core_tb.sv    - 仿真测试代码
```



