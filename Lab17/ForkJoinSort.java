import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.stream.LongStream;
import java.util.Arrays;
import java.util.Random;

interface sortOfArray{ //do not use public!
	void sortUp(long[] numbers);
}

public class ForkJoinSort implements sortOfArray{
	private ForkJoinPool pool;
	private static class SortTask extends RecursiveAction{
		private long[] numbers;
		private int from;
		private int to;

		public SortTask(long[] numbers, int from, int to){
			this.numbers=numbers;
			this.from=from;
			this.to=to;
		}
		protected void compute(){
			if(to-from<2){
				Arrays.sort(numbers,from,to+1);
			}
			else{
				int split=(from+to)/2;
				SortTask f1 = new SortTask(numbers,from,split);
				SortTask f2 = new SortTask(numbers,split+1,to);
				invokeAll(f1,f2);
				Arrays.sort(numbers,from,to+1);
			}
		}
	}
	public ForkJoinSort(){
		pool =new ForkJoinPool();
	}
	public void sortUp(long[]numbers){
		pool.invoke(new SortTask(numbers, 0, numbers.length-1));
	}
	private static void shuffleArr(long[] arr){
		int index;
		long temp;
		Random random = new Random();
		for(int i=arr.length-1;i>0;--i){
			index=random.nextInt(i+1);
			temp=arr[index];
			arr[index]=arr[i];
			arr[i]=temp;
		}
	}	
	public static void main(String[] args){
		long[] numbers = LongStream.rangeClosed(1,100).toArray();
		shuffleArr(numbers);
		System.out.println(Arrays.toString(numbers));
		sortOfArray sort = new ForkJoinSort();
		sort.sortUp(numbers);
		System.out.println(Arrays.toString(numbers));
	}
}
