package cn.xh.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import com.sun.org.apache.xpath.internal.operations.Or;

import cn.xh.dao.OrderDao;
import cn.xh.domain.Music;
import cn.xh.domain.Category;
import cn.xh.domain.Order;
import cn.xh.domain.Orderitem;
import cn.xh.domain.User;
import cn.xh.util.JDBCUtil;
import sun.net.www.content.text.plain;

public class OrderDaoImpl implements OrderDao {

	Connection connection = JDBCUtil.getConnection();

	@Override
	public void save(Order o) {
		try {
			PreparedStatement prepareStatement = connection.prepareStatement(
					"insert into orders (order_id,quantity,money,time,status,user_id) values (?,?,?,?,?,?)");
			prepareStatement.setString(1, o.getOrder_id());
			prepareStatement.setInt(2, o.getQuantity());
			prepareStatement.setDouble(3, o.getMoney());
			prepareStatement.setString(4, o.getTime());
			prepareStatement.setInt(5, o.getStatus());
			prepareStatement.setString(6, o.getUser().getId());
			prepareStatement.executeUpdate();

			// 保存订单项信息
			List<Orderitem> items = o.getItems();
			for (Orderitem item : items) {
				PreparedStatement preparedStatement2 = connection.prepareStatement(
						"insert into orderitems (orderitem_id,quantity,price,music_id,order_id) values(?,?,?,?,?)");
				preparedStatement2.setString(1, item.getOrderitem_id());
				preparedStatement2.setInt(2, item.getQuantity());
				preparedStatement2.setDouble(3, item.getPrice());
				preparedStatement2.setString(4, item.getMusic().getMusic_id());
				preparedStatement2.setString(5, item.getOrder_id());
				preparedStatement2.executeUpdate();
				addMusic_heat(item.getMusic().getMusic_id());
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void addMusic_heat(String music_id) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement(
					"update musicdb set music_heat = music_heat+1,music_inventory=music_inventory-1 where music_id=?");
			prepareStatement.setString(1, music_id);
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public Order findOrderByNum(String order_id) {
		try {
			PreparedStatement prepareStatement = connection.prepareStatement("select * from orders where order_id=?");
			prepareStatement.setString(1, order_id);
			ResultSet rs = prepareStatement.executeQuery();
			Order order = new Order();
			if (rs.next()) {
				order.setOrder_id(rs.getString("order_id"));
				order.setQuantity(rs.getInt("quantity"));
				order.setMoney(rs.getDouble("money"));
				order.setTime(rs.getString("time"));
				order.setStatus(rs.getInt("status"));
				User user = findUserById(rs.getString("user_id"));
				order.setUser(user);
				List<Orderitem> items = finOrdersItemsByNum(rs.getString("order_id"));
				order.setItems(items);
			}
			return order;
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException("");
	}

	// 根据订单id找到订单项
	private List<Orderitem> finOrdersItemsByNum(String order_id) {
		try {
			PreparedStatement prepareStatement = connection
					.prepareStatement("select * from orderitems where order_id=?");
			prepareStatement.setString(1, order_id);
			ResultSet rs = prepareStatement.executeQuery();
			List<Orderitem> list = new ArrayList<Orderitem>();
			while (rs.next()) {
				Orderitem item = new Orderitem();
				item.setOrder_id(order_id);
				Music music = findMusicById(rs.getString("music_id"));
				item.setMusic(music);
				item.setOrderitem_id(rs.getString("orderitem_id"));
				item.setQuantity(rs.getInt("quantity"));
				item.setPrice(rs.getDouble("price"));
				list.add(item);
			}
			return list;
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException("");
	}

	// 根据音乐id找到音乐信息
	private Music findMusicById(String music_id) {
		try {
			PreparedStatement prepareStatement = connection.prepareStatement("select * from musicdb where music_id=?");
			prepareStatement.setString(1, music_id);
			ResultSet rs = prepareStatement.executeQuery();
			Music music = new Music();
			if (rs.next()) {
				music.setMusic_id(rs.getString("music_id"));
				music.setMusic_name(rs.getString("music_name"));
				music.setMusic_singer(rs.getString("music_singer"));
				music.setMusic_lyricist(rs.getString("music_lyricist"));
				music.setMusic_composer(rs.getString("music_composer"));
				music.setRecord(rs.getString("record"));
				music.setRecord_company(rs.getString("record_company"));
				Category category = findCategoryById(rs.getString("music_category"));
				music.setCategory(category);
				music.setFilename(rs.getString("filename"));
				music.setPath(rs.getString("path"));
				music.setMusic_description(rs.getString("music_description"));
				music.setMusic_price(rs.getDouble("music_price"));
				music.setMusic_inventory(rs.getInt("music_inventory"));
				music.setMusic_heat(rs.getInt("music_heat"));
				return music;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException("");
	}

	// 根据音乐分类的id找到音乐分类信息
	private Category findCategoryById(String category_id) {
		Category category = new Category();
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("select * from category where category_id=?");
			preparedStatement.setString(1, category_id);
			ResultSet resultSet = preparedStatement.executeQuery();
			while (resultSet.next()) {
				category.setCategory_id(resultSet.getString("category_id"));
				category.setCategory_name(resultSet.getString("category_name"));
				category.setCategory_description(resultSet.getString("category_description"));
				return category;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException("");
	}

	// 根据id找到用户信息
	private User findUserById(String user_id) {
		try {
			User user = new User();
			PreparedStatement prepareStatement = connection.prepareStatement("select * from user where user_id=?");
			prepareStatement.setString(1, user_id);
			ResultSet rs = prepareStatement.executeQuery();
			if (rs.next()) {
				user.setId(rs.getString("user_id"));
				user.setUsername(rs.getString("user_username"));
			}
			return user;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		throw new RuntimeException("");
	}

	@Override
	public List<Order> findOrdersByUser(String user_id) {
		try {
			PreparedStatement prepareStatement = connection
					.prepareStatement("select * from orders where user_id = ? order by order_id desc");
			prepareStatement.setString(1, user_id);
			ResultSet rs = prepareStatement.executeQuery();
			List<Order> list = new ArrayList<Order>();
			while (rs.next()) {
				Order order = new Order();
				List<Orderitem> items = finOrdersItemsByNum(rs.getString("order_id"));
				order.setItems(items);
				order.setOrder_id(rs.getString("order_id"));
				order.setQuantity(rs.getInt("quantity"));
				order.setMoney(rs.getDouble("money"));
				order.setTime(rs.getString("time"));
				order.setStatus(rs.getInt("status"));
				order.setUser(findUserById(user_id));
				list.add(order);
			}
			return list;
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException("");
	}

	@Override
	public List<Order> findOrders() {
		try {
			PreparedStatement prepareStatement = connection
					.prepareStatement("select * from orders order by order_id desc");
			ResultSet rs = prepareStatement.executeQuery();
			List<Order> list = new ArrayList<Order>();
			while (rs.next()) {
				Order order = new Order();
				List<Orderitem> items = finOrdersItemsByNum(rs.getString("order_id"));
				order.setItems(items);
				order.setOrder_id(rs.getString("order_id"));
				order.setQuantity(rs.getInt("quantity"));
				order.setMoney(rs.getDouble("money"));
				order.setTime(rs.getString("time"));
				order.setStatus(rs.getInt("status"));
				order.setUser(findUserById(rs.getString("user_id")));
				list.add(order);
			}
			return list;
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException("");
	}

	@Override
	public void delivery(String order_id) {
		try {
			PreparedStatement prepareStatement = connection
					.prepareStatement("update orders set status = 1 where order_id=?");
			prepareStatement.setString(1, order_id);
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
