//Cindy Li
import java.util.Scanner;

public class GPA
{
	public static void main(String[] args)
	{
		Scanner input = new Scanner(System.in);
		double[] gpaArr = new double[5];
		double sumGPA = 0;
		double max = 0;
		int iMax = 0;
		int numStudents = 0;//total number of students
		System.out.println("Enter number of A B C D and F grades for the student:");
		for(int i=0; i<5; i++)
		{
			gpaArr[i] = input.nextInt();
			if(max < gpaArr[i])
			{
				max = gpaArr[i];
				iMax = i;
			}
			numStudents += gpaArr[i];
			sumGPA += gpaArr[i] * (4.0-i);
		}
		
		char cMax = 'A';
		if(iMax<4)	//A~D
			cMax = (char)('A'+iMax);
		else	//i==4
			cMax = 'F';
		
		System.out.printf("The grade that student got the most is: %c\n", cMax);
		if(numStudents == 0)
			System.out.printf("No Students!!!");
		else
			System.out.printf("Student Overall GPA: %.2f\n", sumGPA/numStudents);
	}
}