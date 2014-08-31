/*
06/14/1992       MM/DD/YYYY                   by accessor toString
June 14, 1992    Month's name DD, YYYY   by accessor toMonthNameDateString
168 1992           Day of the year YYYY       by accessor toDayDateString
*/

public class Date
{
		private int month;//1-12
		private int day;//1-31
		private int year;//any
		private static String[] monthNames ={"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };
		private int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	//no argument constructor
	public Date()
	{ this(1,1,1);}
	//constructor with int,int,int
	public Date( int mm, int dd, int yy )
	{
				setMonth(mm); // validate month
				setYear(yy); // could validate year
				setDay(dd); // validate day
	} 
	//constructor with String,int,int
	public Date( String mm, int dd, int yy)
	{
				convertMonthName(mm);
				setYear(yy); // could validate year
				setDay(dd); 
	}
	//constructor for int ddd,int yyyy
	public Date(  int ddd, int yy)
	{
			convertFromDayOfYear(ddd);
			setYear(yy);
	}
	// covert Month name to integer,then setMoth() to integer
	public void convertMonthName(String mm)
	{
		System.out.printf("month: %s\n", mm);
		for(int i=0;i<12;i++)
		{
			//System.out.printf("month: %s\n", monthNames[i]);
			if (mm.equalsIgnoreCase(monthNames[i]))
			{
				//System.out.printf("month: %d\n", i);
				setMonth(i+1);
				return;
			}
		}
		return;
	}

	//return number of days in the month
	private int daysInMonth()
	{
		return (leapYear()&&(month == 2))?29:monthDays[month-1];
	}
	//check leapYear
	private boolean leapYear()
	{
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
		else
		return false;
	}

	//setMonth and setDay from ddd yyyy  
	public void convertFromDayOfYear(int ddd)
	{
		int dayTotal=0;
		if (ddd<1 ||ddd>366)//check invalid day
			throw new IllegalArgumentException("invalid DayOfYear");
		else
			for (int m=1;m<13&&(dayTotal+daysInMonth())<ddd;m++)
			{
				dayTotal += daysInMonth();
				setMonth(m+1);//set month
			}//end for loop
		setDay(ddd-dayTotal);
	}

	// from mm/dd/yyyy to ddd yyyy,calculate day of year
	private int convertToDayOfYear()
	{
		int ddd =0;
		for (int m=1;m<=month-1;m++)
		{
			if (leapYear() && m==2)
				ddd+=29;
			else
				ddd+=monthDays[m-1];
			System.out.printf("ddd: %d\n", ddd);
		}
		ddd+=day;
		return ddd;
	}


	public String toString() 
	 { 
	 return String.format( "%d/%d/%d", month, day, year );
	 } // method return mm/dd/yy

	 // return Date in format: MonthName dd, yyyy
	public String toMonthNameDateString()
	 { 
		return String.format( "%s %d, %d", monthNames[ month - 1 ], day, year );
		} // end method toMonthNameDateString

	 // return Date in format DDD YYYY
	public String toDayOfYearString() 
		{ 
		return String.format( "%d %d", convertToDayOfYear(), year );
		} // end method toDayDateString
	

	//set and get method
	public void setMonth(int mm)
	{
		month = ( mm >= 1 && mm <= 12 ) ? mm : 1;
		// System.out.printf("month: %d\n", month);
	}
	public void setDay(int dd)
	{
		day = ( dd >= 1 && dd <= daysInMonth() ) ? dd : 1;
		// System.out.printf("day:  %d\n", day);
	}
	public void setYear(int yy)
	{
		year=yy;
	}
	public int getMonth()
	{
		return month;
	}
	public int getDay()
	{
		return day;
	}
	public int getYear()
	{
		return year;
	}
		 

}