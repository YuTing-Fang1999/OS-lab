import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.stream.LongStream;

interface sumOfArray{ //do not use public!
	long sumUp(long[] numbers);
}

public class ForkJoinSum implements sumOfArray{
	private ForkJoinPool pool;
	private static class SumTask extends RecursiveTask<Long>{
		private long[] numbers;
		private int from;
		private int to;

		public SumTask(long[] numbers, int from, int to){
			this.numbers=numbers;
			this.from=from;
			this.to=to;
		}
		protected Long compute(){
			if(to-from<6){
				long total=0;
				for(int i=from;i<=to;++i){
					total+=numbers[i];
				}
				return total;
			}
			else{
				int split=(from+to)/2;
				SumTask f1 = new SumTask(numbers,from,split);
				SumTask f2 = new SumTask(numbers,split+1,to);
				f1.fork();
				return f2.compute()+f1.join();
			}
		}
	}
	public ForkJoinSum(){
		pool =new ForkJoinPool();
	}
	public long sumUp(long[]numbers){
		return pool.invoke(new SumTask(numbers, 0, numbers.length-1));
	}
	
	public static void main(String[] args){
		long[] numbers = LongStream.rangeClosed(1,1000).toArray();
		sumOfArray sum = new ForkJoinSum();
		System.out.println(sum.sumUp(numbers));
	}
}
