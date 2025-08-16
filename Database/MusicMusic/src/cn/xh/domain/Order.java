package cn.xh.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

//����
public class Order implements Serializable {
	private String order_id;// ������
	private int quantity;// ����������
	private double money;// �ܽ��
	private String time;// ��������ʱ��
	private int status;// ����״̬��0δ���1�Ѹ��2δ������3�ѷ���
	private User user;// �ͻ�
	private List<Orderitem> items = new ArrayList<Orderitem>();// ������


	public String getOrder_id() {
		return order_id;
	}
	public void setOrder_id(String order_id) {
		this.order_id = order_id;
	}

	public int getQuantity() {
		return quantity;
	}
	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}

	public double getMoney() {
		return money;
	}
	public void setMoney(double money) {
		this.money = money;
	}

	public String getTime() {
		return time;
	}
	public void setTime(String time) {
		this.time = time;
	}

	public User getUser() {
		return user;
	}
	public void setUser(User user) {
		this.user = user;
	}

	public List<Orderitem> getItems() {
		return items;
	}
	public void setItems(List<Orderitem> items) {
		this.items = items;
	}

	public int getStatus() {
		return status;
	}
	public void setStatus(int status) {
		this.status = status;
	}

	public Order() {
		super();
		// TODO Auto-generated constructor stub
	}

	public Order(String order_id, int quantity, double money, String time, int status, User user,
			List<Orderitem> items) {
		super();
		this.order_id = order_id;
		this.quantity = quantity;
		this.money = money;
		this.time = time;
		this.status = status;
		this.user = user;
		this.items = items;
	}

	@Override
	public String toString() {
		return "Order [order_id=" + order_id + ", quantity=" + quantity + ", money=" + money + ", time=" + time
				+ ", status=" + status + ", user=" + user + ", items=" + items + "]";
	}

}
