import java.lang.Thread;
import java.util.concurrent.locks.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.LinkedList;
import java.util.Queue;
abstract class init extends Thread{
	public static Lock lock=new ReentrantLock();
	public static Condition threadcond=lock.newCondition();
	public static int product=0;
}
public class warehouse extends init{

public static void main(String[] args){
	Runnable a=new getproduct();
	Runnable b=new setproduct();
	Thread produce=new Thread(b);
	Thread consume=new Thread(a);
	produce.start();
	consume.start();
	try{
		consume.join();
		produce.join();
	}
	catch(InterruptedException e){}
}
}
class setproduct extends init{
	public void run(){
		while(true){
		lock.lock();
		try{
			while(product==10){
				try{
					System.out.println("full");
					threadcond.await();
				}
				catch(InterruptedException e){
					e.printStackTrace();
				}
			}
			//for(int i=0;i<10;++i){
				product++;
				System.out.println("producer"+Thread.currentThread().getId()+": product+1 amount="+product);
				threadcond.signal();
			//}
		}
		finally
		{
			lock.unlock();
		}
		}
	}
}
class getproduct extends init{
	public void run(){
		while(true){
		lock.lock();
		try{
			while(product==0){
				try{
					System.out.println("empty");
					threadcond.await();
				}
				catch(InterruptedException e){
					e.printStackTrace();
				}
			}
			//for(int i=0;i<10;++i){
				product--;
				System.out.println("			comsumer"+Thread.currentThread().getId()+": product-1 amount="+product);
				threadcond.signal();
			//}
		}
		finally
		{
			lock.unlock();
		}
		}
	}
}
