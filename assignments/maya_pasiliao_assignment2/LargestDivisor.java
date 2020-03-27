package assignments.maya_pasiliao_assignment2;

public class LargestDivisor {
  public static void main(final String[] args) throws InterruptedException {
    int threadCount = 1;
    Divisors[] threads = new Divisors[threadCount];
    long startTime = System.currentTimeMillis();

    for(int k = 0; k < threadCount; k++) {
      int lower = k * 10000 / threadCount;
      int upper = (k + 1) * 10000 / threadCount;
      threads[k] = new Divisors(lower, upper);
      threads[k].start();
    }

    int count = 0;
    while(count < threadCount) {
      threads[count].join();
      count++;
    }

    long endTime = System.currentTimeMillis();
    long elapsedTime = endTime - startTime;

    int result = -1, maxFactor = 0;
    for(int k = 0; k < threadCount; k++) {
      if(threads[k].factorCount > maxFactor) {
        maxFactor = threads[k].factorCount;
        result = threads[k].answer;
      }
    }
    System.out.printf("Number with largest number of divisors: %d\n", result);
    System.out.printf("Total Execution time (in milliseconds): %d\n", elapsedTime);
  }
}

// Implementing the Thread interface to find factor count
class Divisors extends Thread {
  int lower, upper, answer;
  int factorCount = 0;

  Divisors(int lower_bound, int upper_bound) {
    lower = lower_bound;
    upper = upper_bound;
    // answer = -1; // final answer for this thread
  }

  int getFactorCount(int number) {
    for(int k = 1; k <= number; k++)
      if(number % k == 0)
        factorCount++;
    return factorCount;
  }

  // Override run method
  @Override
  public void run() {
    for(int k = lower; k <= upper; k++) {
      int count = getFactorCount(k);
      if(count > factorCount) {
        factorCount = count;
        answer = k;
      }
    }
  }
}
