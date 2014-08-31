public  class SalesBill 
{
	private String name;
	private int salesAmount;
	private double taxRate; //percent

	public SalesBill(String cName) 
	{
		this(cName, 0, 0.0);
	}

	public SalesBill(String cName, int cSalesAmout, double cTaxRate) 
	{
		setName(cName);
		setSalesAmount(cSalesAmout);
		setTaxRate(cTaxRate);
	}

	// set method
	public void setName(String cName) 
	{
		name = cName;
	}

	public void setSalesAmount(int cSalesAmout) 
	{
		salesAmount = cSalesAmout;
	}

	public void setTaxRate(double cTaxRate) 
	{
		taxRate = cTaxRate;
	}

	// get method
	public String getName() 
	{
		return name;
	}

	public int getSalesAmount() 
	{
		return salesAmount;
	}
	
	public double getTaxRate() 
	{
		return taxRate;
	}

	public double getTotalCharge() 
	{
		return salesAmount * (1.0 + taxRate);
	}
	
	@Override
	public String toString()
	{
		return String.format( "Customer:%s\nSales:$%s\tTax:%s%%\tTotal Charge:$%s\n", 
			getName(), getSalesAmount(), getTaxRate(), getTotalCharge());
	}
}
