package assignments.maya_pasiliao_assignment2;

public class LargestDivisor {
  public static void main(final String[] args) throws InterruptedException {
    int threadCount = 275;
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


// public static void main(String[] args) throws Exception {

//   int numOfThreads = 2; // number _of _threads to be executed for this purpose

//   FactorClass[] threadList = new FactorClass[numOfThreads];

//   long startTime = System.currentTimeMillis(); // timer start

//   for (int lv = 0; lv < numOfThreads; lv++) {

//       int lower = lv * 10000 / numOfThreads;

//       int upper = (lv + 1) * 10000 / numOfThreads;

//       threadList[lv] = new FactorClass(lower,upper ); // create thread

//       threadList[lv].start();  //start thread

//   }

//   for (int i = 0; i < numOfThreads; i++)

//       threadList[i].join();  //wit until each thred isn't finished

//   long endTime = System.currentTimeMillis();

//   int result = -1, maxFactor = 0;

//   for (int lv = 0; lv < numOfThreads; lv++) { // find result among threads

//       if (threadList[lv].numOfFactors > maxFactor) {

//           maxFactor = threadList[lv].numOfFactors;

//           result = threadList[lv].answer;

//       }

//   }

//   System.out.println("Number with maximum factors: " + result);

//   System.out.println("Factors of number: " + maxFactor);

//   System.out.println("Total Number of Threads used: " + numOfThreads);

//   System.out.println("Total Execution time (in milliseconds): " + (endTime - startTime));

// }

// }

// class FactorClass extends Thread {

// int lower, upper, answer, numOfFactors;

// FactorClass(int lower_bound, int upper_bound) {

//   lower = lower_bound;

//   upper = upper_bound;

//   numOfFactors = 0;

//   answer=-1; //final answer for this thread

// }
// class FactorClass extends Thread {

//   int lower, upper, answer, numOfFactors;

//   FactorClass(int lower_bound, int upper_bound) {

//       lower = lower_bound;

//       upper = upper_bound;

//       numOfFactors = 0;

//       answer=-1; //final answer for this thread

//   }

//   private int getNumberOfFactors(int number) { // factorize  1 number and return number of factors

//       int countFactor = 0;

//       for (int lv = 1; (lv) <= number; lv++)

//           if (number % lv == 0)

//               countFactor++;

//       return countFactor;

//   }

//   @Override

//   public void run() {

//       for (int lv = lower; lv <= upper; lv++) {

//           int count = getNumberOfFactors(lv);

//           if (count > numOfFactors) {

//               numOfFactors = count;

//               answer = lv;

//           }

//       }

//   }

// }
