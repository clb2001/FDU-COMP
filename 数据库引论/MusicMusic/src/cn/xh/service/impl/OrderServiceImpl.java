package cn.xh.service.impl;

import java.util.List;

import cn.xh.dao.OrderDao;
import cn.xh.dao.impl.OrderDaoImpl;
import cn.xh.domain.Order;
import cn.xh.domain.Orderitem;
import cn.xh.domain.User;
import cn.xh.service.OrderService;

public class OrderServiceImpl implements OrderService {
	private final OrderDao dao = new OrderDaoImpl();

	@Override
	public void generateOrder(Order o) {
		if (o.getUser() == null) {
			throw new IllegalArgumentException("�޶��������Ŀͻ���Ϣ");
		}
		if (o.getItems() == null || o.getItems().size() == 0) {
			throw new IllegalArgumentException("������û�ж�����");
		}
		dao.save(o);
	}

	@Override
	public Order findOrderByNum(String order_id) {
		return dao.findOrderByNum(order_id);
	}

	@Override
	public List<Order> findUserOrders(User user) {
		return dao.findOrdersByUser(user.getId());
	}

	@Override
	public List<Order> findOrders() {
		// TODO Auto-generated method stub
		return dao.findOrders();
	}

	@Override
	public void delivery(String order_id) {
		// TODO Auto-generated method stub
		dao.delivery(order_id);
	}
}
