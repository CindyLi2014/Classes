
import java.util.Scanner;

public class DateTest
{
	
	public static void main(String[] args)
	{
				//Date myDate = new Date(9, 16, 2011);
        //Date myDate2 = new Date("June", 24, 2010);
        //Date myDate3 = new Date(259, 2005);

        // all three dates above are equal and will therefore print
        // the same dates

        //System.out.println(myDate);
				//System.out.printf("myDate Month DD YYY :%s",myDate.toStringmonth());
        //System.out.println(myDate2);
        //System.out.println(myDate3); 

		
		Scanner input=new Scanner(System.in);
		int choice;
		while(true)
		{
			int month;
			int day;
			int year;
			String monthName;
			Date date = new Date();
			
		System.out.println("Enter 1 for format: MM/DD/YYYY");
		System.out.println("Enter	2 for format: Month DD YYYY");
		System.out.println("Enter 3 for format: DDD YYYY");			
		System.out.println("Enter 4 to exit");
		choice=input.nextInt();
		if (choice == 1)
		{
		
		System.out.println("Enter Month (1-12):");
		date.setMonth(input.nextInt());
		System.out.println("Enter Day of Month:");
		date.setDay(input.nextInt());
		System.out.println("Enter Year:");
		date.setYear(input.nextInt());
		}
		if (choice == 2)
		{
		
		System.out.println("Enter Month in name:");
		monthName=input.next();
		date.convertMonthName(monthName);
		System.out.println("Enter Day of Month:");
		date.setDay(input.nextInt());
		System.out.println("Enter Year:");
		date.setYear(input.nextInt());
		}
		if (choice == 3)
		{
		System.out.println("Enter Day of Year");
		int dayTemp = input.nextInt();
		System.out.println("Enter Year:");
		date.setYear(input.nextInt());
		date.convertFromDayOfYear(dayTemp);
		}
		if (choice==4)
		break;
				
		System.out.printf("\n%s: %s\n%s: %s\n%s: %s\n",
		"MM/DD/YYYY",date.toString(),
		"Month DD,YYYY",date.toMonthNameDateString(),
		"DDD YYYY",date.toDayOfYearString());
		//System.out.printf("MM/DD/YY %d/%d/%d\n",date1.getMonth(),date1.getDay(),date1.getYear());
		//System.out.printf("MM/DD/YYYY:%d/%d/%d",date1.month,date1.day,date1.year);
	//	System.out.printf("MM/DD/YYYY:%s/%d/%d",date1.toStringmonth(),,date1.getYear());
	//System.out.printf("Month,dd,yyy %s\n",date1.toStringmonth());
		//System.out.printf("Month,DD,YYYY%s,%d,%d",date1.covertInt2monthname(mm),dd,yy);
		//System.out.printf("DDD,YYYY%d %d",date1.convertdd2ddd(mm,dd,yy);
		
		
		}
		
	}
}