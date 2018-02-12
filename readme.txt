This project name is mylinux, it create by bain.wang

total lines: 200973

------------
This is a complete engineering path, but only the igmp-snooping source code is open. Other modules are provided in a static library, which can be downloaded and compiled freely, and can be adjusted by the cliImage process for igmp-snooping.
The project consists of four processes:
1. The main process bcImage provides IPC communication and the implementation of each function;
2. Process cli, which provides command line function;
3. SNMP, provides the simple network management protocol function;
4. Test, a test function, has no real meaning.
Igmp-snooping is in the main process.
The API documentation will be provided as soon as possible, and it will support configuring the igmp via cli or SNMP.

                                          ---- bain.wang@outlook.com



------------
introduce
------------

dir info:
--------common：--------公共模块；提供工程各进程使用的公共接口实现。
----------------ipc：-----------进程间通信，CPU进程间及CPU间通信
----------------log：-----------日志；记录系统日志
----------------message：-------消息；结合中英文对输出信息统一管理
----------------modules：-------模块；统一管理各功能模块ID
----------------platform：------平台；提供进程/线程/信号量/锁/队列/内存/信号/定时器/中断的接口
----------------print：---------输出；提供多种统一的debug模块
----------------util：----------数据结构；提供bit/block/list/tree/hash接口、ip/mac操作接口、回调接口，及字符串接口
----------------vfs：-----------文件操作；提供统一的文件操作接口
--------module：--------模块功能；主进程中各模块实现
----------------startup：-------启动；main函数所在
----------------system：--------系统；系统相关功能
------------------------baseinfo：------系统基本信息；包括事件、轮循接口，以及ip、mac信息，ip与mac支持外部
------------------------binchie：-------开发人员信息；本工程开发所参与的全部人员系统，支持外部
------------------------cli：-----------cli的进程间通信；cli充当服务端，主进程充当客户端，用于双向通信，服务端支持外部
------------------------filetrans：-----系统升级；用于对设备升级，支持外部
------------------------ipc：-----------提供ipc的创建与删除，debug等，支持外部
------------------------log：-----------提供日志的操作，支持外部
------------------------platform：------platform的debug，支持外部
------------------------print：---------debug模块操作，支持外部
------------------------session：-------会话管理，配合ipc完成进程间通信，支持外部
------------------------test：----------测试事件及poolling，无意义，不支持外部
------------------------usermgmt：------cli账户管理，支持外部
------------------------clock：---------时钟；用于设置及查看系统时区及时间，支持外部
------------------------cfgmgmt：-------配置管理；用于通过加载配置及记录通过cli操作的命令等；支持外部
------------------------stats：---------性能统计；产生设备性能参数的当前/15分钟/24小时统计信息，含门限告警；支持外部
--------processes：-----子进程
----------------other：---------测试进程；无意义，支持单向通信
----------------mycli：---------命令行进程
------------------------cli_mini：------独立的cli进程；主要用于升级失败时的紧急处理
------------------------cli：-----------完整的cli；集成上述部分功能，提供对设备的管理，支持双向通信
----------------snmp：----------网络管理协议；支持V3,支持trap且可配置，集成烽火ptn部分结点
--------include：-------头文件；主进程各模块的头文件
--------lib_a：---------静态库；包含了主进程中对外提供的静态库
--------image：---------主进程及各子进程的可执行文件，不含cli_mini
--------si：------------sourceInsight工程目录
--------tmp：-----------备份文件；不影响工程编译
file:
--------tree.txt：--------------工程tree
--------build result.txt：------编译过程
--------readme.txt：------------本文件
			
======================================================================