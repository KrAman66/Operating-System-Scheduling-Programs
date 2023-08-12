import java.util.Scanner;

public class Bankers {
    int n; // Number of processes
    int m; // Number of resources
    int need[][];
    int[][] max;
    int[][] alloc;
    int[] avail;
    int[] safeSequence;

    void initializeValues() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        n = scanner.nextInt();

        System.out.print("Enter the number of resources: ");
        m = scanner.nextInt();

        need = new int[n][m];
        max = new int[n][m];
        alloc = new int[n][m];
        avail = new int[m];
        safeSequence = new int[n];

        // Input Allocation Matrix
        System.out.println("Enter the Allocation Matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                alloc[i][j] = scanner.nextInt();
            }
        }

        // Input Maximum Matrix
        System.out.println("Enter the Maximum Matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                max[i][j] = scanner.nextInt();
            }
        }

        // Input Available Resources
        System.out.println("Enter the number of available instances of each resource:");
        for (int i = 0; i < m; i++) {
            avail[i] = scanner.nextInt();
        }

        scanner.close();
    }

    // ... (rest of the code remains unchanged)
    void isSafe()
    {
    int count=0;
     
    //visited array to find the already allocated process
    boolean visited[] = new boolean[n];
    for (int i = 0;i < n; i++)
    {
        visited[i] = false;
    }
         
    //work array to store the copy of available resources
    int work[] = new int[m];   
    for (int i = 0;i < m; i++)
    {
        work[i] = avail[i];
    }
 
    while (count<n)
    {
        boolean flag = false;
        for (int i = 0;i < n; i++)
        {
            if (visited[i] == false)
             {
            int j;
            for (j = 0;j < m; j++)
            {       
                if (need[i][j] > work[j])
                break;
            }
            if (j == m)
            {
               safeSequence[count++]=i;
               visited[i]=true;
               flag=true;
                         
                for (j = 0;j < m; j++)
                {
                work[j] = work[j]+alloc[i][j];
                }
            }
             }
        }
        if (flag == false)
        {
            break;
        }
    }
    if (count < n)
    {
        System.out.println("The System is UnSafe!");
    }
    else
    {
        //System.out.println("The given System is Safe");
        System.out.println("Following is the SAFE Sequence");
                for (int i = 0;i < n; i++)
        {
            System.out.print("P" + safeSequence[i]);
            if (i != n-1)
            System.out.print(" -> ");
        }
    }
    }
    

    void calculateNeed()
    {
    for (int i = 0;i < n; i++)
    {
        for (int j = 0;j < m; j++)
         {
        need[i][j] = max[i][j]-alloc[i][j];
         }
    }       
    }


    void printMatrixColumnForm(String matrixName, int[][] matrix) {
        System.out.println(matrixName + ":");
        for (int j = 0; j < m; j++) {
            System.out.print("\tR" + j);
        }
        System.out.println();
        for (int i = 0; i < n; i++) {
            System.out.print("P" + i);
            for (int j = 0; j < m; j++) {
                System.out.print("\t" + matrix[i][j]);
            }
            System.out.println();
        }
    }
     
    void printMatrix(int[][] matrix) {
        System.out.println("Matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(matrix[i][j] + "\t");
            }
            System.out.println();
        }
    }

    void printArray(int[] array) {
        System.out.println("Array:");
        for (int i = 0; i < m; i++) {
            System.out.print(array[i] + "\t");
        }
        System.out.println();
    }

    void printArrayColumnForm(String arrayName, int[] array) {
        System.out.println(arrayName + ":");
        for (int i = 0; i < m; i++) {
            System.out.println("\tR" + i + ": " + array[i]);
        }
    }

    void printNeedColumnForm() {
        System.out.println("Need Matrix:");
        for (int j = 0; j < m; j++) {
            System.out.print("\tR" + j);
        }
        System.out.println();
        for (int i = 0; i < n; i++) {
            System.out.print("P" + i);
            for (int j = 0; j < m; j++) {
                System.out.print("\t" + need[i][j]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Bankers gfg = new Bankers();

        gfg.initializeValues();

        System.out.println("Input Values:");
        gfg.printMatrixColumnForm("Allocation Matrix", gfg.alloc);
        gfg.printMatrixColumnForm("Maximum Matrix", gfg.max);
        gfg.printArrayColumnForm("Available Matrix", gfg.avail);

        gfg.calculateNeed();
        gfg.printNeedColumnForm();
        gfg.isSafe();

        System.out.println("\n Output Values:\n");
        gfg.printMatrix(gfg.need);
        gfg.printArray(gfg.safeSequence);
    }
}