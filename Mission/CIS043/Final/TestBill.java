public class TestBill 
{
	public static void main(String[] args) 
	{
		SalesBill john1 = new SalesBill("John Smith");
		john1.setSalesAmount(80);
		john1.setTaxRate(0.085);
		
		SalesBill john2 = new SalesBill("John Smith", 200, 0.06);
		
		SalesBill jane = new ServiceBill("Jane Smith", 60, 0.085, 12);
		
		SalesBill[] customers = new SalesBill[3];
		customers[0] = john1;
		customers[1] = john2;
		customers[2] = jane;
		
		double totalCharge = 0.0;
		for(SalesBill customer : customers)
		{
			totalCharge += customer.getTotalCharge();
			System.out.println(customer);
		}
		
		System.out.printf("Grand Total Charge: $%s", totalCharge);
	}
}
