package cn.xh.dao;

import java.util.List;

import cn.xh.domain.Order;

public interface OrderDao {

	void save(Order o);

	Order findOrderByNum(String order_id);

	List<Order> findOrdersByUser(String user_id);

	List<Order> findOrders();

	// 这代码命名真是辣鸡
	void delivery(String order_id);

}
