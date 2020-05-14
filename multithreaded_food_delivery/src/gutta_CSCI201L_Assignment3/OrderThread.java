package gutta_CSCI201L_Assignment3;

import java.util.Vector;

public class OrderThread extends Thread{
	private Order order;
	Vector<Order> ready_orders;
	
	OrderThread(Order order, Vector<Order> ready_orders){
		this.order = order;
		this.ready_orders = ready_orders;
	}
	
	public void run() {
		int time = this.order.time;
		try {
			Thread.sleep(time*1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ready_orders.add(this.order);
	}
}
