public class ServiceBill extends SalesBill 
{
	private double tip;

	public ServiceBill(String cName, int cSalesAmout, double cTaxRate, double cTip ) 
	{
		super(cName, cSalesAmout, cTaxRate);
		setTip(cTip);
	}
	
	public void setTip(double cTip) 
	{
		if (cTip > 0) 
			tip = cTip;
		else
			tip = 0;
	}
	
	public double getTip()
	{
		return tip;
	}
	
	@Override
	public double getTotalCharge() 
	{
		return super.getTotalCharge() + tip;
	}
	
	@Override
	public String toString()
	{
		return String.format( "Customer:%s\nSales:$%s\tTax:%s%%\tTip:$%s\tTotal Charge:$%s\n", 
			getName(), getSalesAmount(), getTaxRate(), getTip(), getTotalCharge());
	}
	
}
