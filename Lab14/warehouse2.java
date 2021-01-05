import java.lang.Thread;
import java.util.concurrent.locks.*;
import java.util.concurrent.locks.ReentrantLock;

public class warehouse2{
	public static Lock lock=new ReentrantLock();
	public static Condition threadcond=lock.newCondition();
	public static int product=0;

public static void setproduct(){
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
public static void  getproduct(){
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

public static void main(String[] args){
	Thread produce=new Thread(()->{setproduct();});
	Thread consume=new Thread(()->{getproduct();});
	produce.start();
	consume.start();
	try{
		consume.join();
		produce.join();
	}
	catch(InterruptedException e){}
}
}

