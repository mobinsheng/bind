# bind
基于webrtc的rtcbase实现的闭包，当需要异步/延迟执行某个函数的时候非常有用



  基于webrtc内部rtcbase实现的闭包
  它最大的优势是可以用Closure来表示各种各样的函数（参数类型、参数长度、返回值都可以不同）
  这是一个很大的优势，因为这样我们就可以使用一个队列来存放不同类型的闭包，然后异步执行
 
  这个优势可以通过下面的例子来说明：
  假设有这样的一个需求：有两个线程A和B，要求在线程A里面投递一个任务让线程B执行
  一般的做法是：
  
  1、构造一个队列
  
  2、把任务（函数）和相关参数封装成结构体，然后放入队列里
  
  3、线程B循环读取队列里的任务，执行任务
  
  这样做可以满足要求，但是仔细思考一下，如果我们有很多个参数不同的函数，每个函数都要投递给线程B执行，如下所示
  
  void f1(int){};
  
  void f2(int,int){}
  
  void f3(int,double,const char){}
  
  .....
  
  void fn(double,int,std::stirng,...,int){}
  
  如果还是按照这种方法，那我们岂不是要构造n个不同类型的结构体（因为各个函数的参数类型和数量都不一样，所以每个函数都要一种结构体保存参数）去保存参数，然后创建n个不同队列去存放任务
  
  这样岂不是太麻烦了，这时候使用Closure就可以完美解决问题，如下所示：
  
  int v1 = 0;
  
  double v2 =0;
  
  const char v3 = "";
  
  std::string v4 = "";
 
  Closure c1 = lazy::CreateClosure(lazy::Bind(f1,v1));
  
  Closure c2 = lazy::CreateClosure(lazy::Bind(f2,v1,v2));
  
  Closure c3 = lazy::CreateClosure(lazy::Bind(f3,v1,v2,v3));
  
  Closure c4 = lazy::CreateClosure(lazy::Bind(f4,v1,v2,v3,v4));
 
  std::deque<Closure> task_list;
  
  task_list.push_back(c1);
  
  task_list.push_back(c2);
  
  task_list.push_back(c3);
  
  task_list.push_back(c4);
 
  for(int i = 0; i < task_list.size(); ++i){
  
       Closure closure = task_list[i];
       
       closure(); // 执行task
       
  }
