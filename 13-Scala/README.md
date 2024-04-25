# Spark Assignment

## Installation

1. Install Scala:

   ```bash
   sudo apt install scala
   # Password for student: student
   ```
3. Verify Scala version:

   ```bash
   scala -version
   ```
5. Download a packaged release of Spark from <https://spark.apache.org/downloads.html>
6. `cd` to the folder where you have downloaded Spark and run:

   ```bash
   # Extract Spark
   tar xvf spark-3.5.1-bin-hadoop3.tgz

   # Enter Super-User mode (password for PICT machines: root123)
   su

   # ----- SU MODE -----
   cd Downloads

   # Move spark to usr/local
   mv spark-3.5.1-bin-hadoop3 /usr/local/spark

   # ----- EXIT SU MODE -----
   exit
   ```
8. Add Spark as an environment variable

   ```bash
   export PATH=$PATH:/usr/local/spark/bin
   source ~/.bashrc
   ```
10. Run spark shell

    ```bash
    spark-shell
    ```
## Assignment

```scala
val input = sc.textFile("input1.txt")

// Create a new RDD by splitting the input RDD on the basis of space
val words = input.flatMap(x => x.split(" "))

// Create a new RDD by mapping each word to a tuple of (word, 1)
val counts = words.map(x => (x, 1))

// Create a new RDD by reducing the tuples by key
val reducedCounts = counts.reduceByKey((x, y) => x + y)

// Save the RDD to a file
reducedCounts.saveAsTextFile("output1.txt")

// Print the contents of the file
reducedCounts.foreach(println)
```
