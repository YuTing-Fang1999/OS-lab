import java.lang.Thread;
public class test{
	public static int c=0;
	static synchronized void add(){
		for(int i=0;i<25000000;++i) ++c;	
	}
	static synchronized void sub(){
		for(int i=0;i<25000000;++i) --c;	
	}

public static void main(String[] args){
	Thread add1=new Thread(()->{add();});
	Thread add2=new Thread(()->{add();});
	Thread sub1=new Thread(()->{sub();});
	Thread sub2=new Thread(()->{sub();});
	add1.start();
	add2.start();
	sub1.start();
	sub2.start();
	try{
		add1.join();
		add2.join();
		sub1.join();
		sub2.join();
	}
	catch(InterruptedException e){}
	System.out.println(c);
}
}
