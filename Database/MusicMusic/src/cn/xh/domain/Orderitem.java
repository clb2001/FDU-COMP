package cn.xh.domain;

import java.io.Serializable;

//订单项
public class Orderitem implements Serializable {
	private String orderitem_id;// 订单项id
	private int quantity;// 订单项数量
	private double price;// 订单项小计
	private Music music;
	private String order_id;

	public String getOrderitem_id() {
		return orderitem_id;
	}
	public void setOrderitem_id(String orderitem_id) {
		this.orderitem_id = orderitem_id;
	}

	public int getQuantity() {
		return quantity;
	}
	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}

	public double getPrice() {
		return price;
	}
	public void setPrice(double price) {
		this.price = price;
	}

	public Music getMusic() {
		return music;
	}
	public void setMusic(Music music) {
		this.music = music;
	}

	public String getOrder_id() {
		return order_id;
	}
	public void setOrder_id(String order_id) {
		this.order_id = order_id;
	}

	public Orderitem(String orderitem_id, int quantity, double price, Music music, String order_id) {
		super();
		this.orderitem_id = orderitem_id;
		this.quantity = quantity;
		this.price = price;
		this.music = music;
		this.order_id = order_id;
	}

	@Override
	public String toString() {
		return "Orderitem [orderitem_id=" + orderitem_id + ", quantity=" + quantity + ", price=" + price +
				", music=" + music + ", order_id=" + order_id + "]";
	}

	public Orderitem() {
		super();
		// TODO Auto-generated constructor stub
	}

}
