package cn.xh.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import com.sun.xml.internal.ws.api.addressing.AddressingVersion.EPR;

import cn.xh.dao.ManagerDao;
import cn.xh.domain.Administrator;
import cn.xh.domain.Music;
import cn.xh.domain.Category;
import cn.xh.domain.User;
import cn.xh.util.JDBCUtil;

public class ManagerDaoImpl implements ManagerDao {

	// 管理员登录
	@Override
	public Administrator login(String username, String password) {
		Administrator admin = new Administrator();
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("select * from administrator where admin_username=? and admin_password=?");
			prepareStatement.setString(1, username);
			prepareStatement.setString(2, password);
			ResultSet rs = prepareStatement.executeQuery();
			if (rs.next()) {
				admin.setUsername(rs.getString("admin_username"));
				admin.setPassword(rs.getString("admin_password"));
				admin.setName(rs.getString("admin_name"));
				admin.setSex(rs.getString("admin_sex"));
				admin.setTel(rs.getString("admin_tel"));
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return admin;
	}

	// 管理员信息修改
	@Override
	public void managerInformation(Administrator admin) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement(
					"update administrator set admin_name=?, admin_sex=?, admin_tel=? where admin_username=? ");
			prepareStatement.setString(1, admin.getName());
			prepareStatement.setString(2, admin.getSex());
			prepareStatement.setString(3, admin.getTel());
			prepareStatement.setString(4, admin.getUsername());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// 管理员登录密码修改
	@Override
	public void managerPassword(Administrator admin) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("update administrator set admin_password=? where admin_username=?");
			prepareStatement.setString(1, admin.getPassword());
			prepareStatement.setString(2, admin.getUsername());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// 获得所有音乐分类信息
	@Override
	public List<Category> findAllCategory() {
		List<Category> list = new ArrayList<Category>();
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement preparedStatement = connection.prepareStatement("select * from category");
			ResultSet rs = preparedStatement.executeQuery();
			while (rs.next()) {
				Category category = new Category();
				category.setCategory_id(rs.getString("category_id"));
				category.setCategory_name(rs.getString("category_name"));
				category.setCategory_description(rs.getString("category_description"));
				list.add(category);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return list;
	}

	// 通过分类id找到分类信息
	@Override
	public Category findCategoryById(String category_id) {
		Category category = new Category();
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("select * from category where category_id = ?");
			prepareStatement.setString(1, category_id);
			ResultSet rs = prepareStatement.executeQuery();
			if (rs.next()) {
				category.setCategory_id(rs.getString("category_id"));
				category.setCategory_name(rs.getString("category_name"));
				category.setCategory_description(rs.getString("category_description"));
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return category;
	}

	// 添加音乐
	@Override
	public void addMusic(Music music) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("insert into musicdb values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
			prepareStatement.setString(1, music.getMusic_id());
			prepareStatement.setString(2, music.getMusic_name());
			prepareStatement.setString(3, music.getMusic_singer());
			prepareStatement.setString(4, music.getMusic_lyricist());
			prepareStatement.setString(5, music.getMusic_composer());
			prepareStatement.setString(6, music.getRecord());
			prepareStatement.setString(7, music.getRecord_company());
			prepareStatement.setString(8, music.getCategory().getCategory_id());
			prepareStatement.setString(9, music.getFilename());
			prepareStatement.setString(10, music.getPath());
			prepareStatement.setString(11, music.getMusic_description());
			prepareStatement.setDouble(12, music.getMusic_price());
			prepareStatement.setInt(13, music.getMusic_inventory());
			prepareStatement.setInt(14, music.getMusic_heat());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// 添加音乐分类
	@Override
	public void addCategory(Category category) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement("insert into category values(?,?,?)");
			prepareStatement.setString(1, category.getCategory_id());
			prepareStatement.setString(2, category.getCategory_name());
			prepareStatement.setString(3, category.getCategory_description());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	//分类音乐
	@Override
	public List<Music> getCategoryMusic(String cid) {
		ClientDaoImpl clientDaoImpl = new ClientDaoImpl();
		return clientDaoImpl.getCategoryMusic(cid);
	}


	// 根据音乐id找到音乐信息
	@Override
	public Music findMusicById(String music_id) {
		Music music = new Music();
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement("select * from musicdb where music_id = ?");
			prepareStatement.setString(1, music_id);
			ResultSet rs = prepareStatement.executeQuery();
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
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return music;
	}

	// 删除音乐
	@Override
	public void delMusic(String music_id) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement(" delete from musicdb where music_id=?");
			prepareStatement.setString(1, music_id);
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void editMusic(String music_id, String music_name, String music_singer, String music_lyricist,
						  String music_composer, String record, String record_company, String music_description,
						  double music_price, String music_inventory) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement(
					"update musicdb set music_name=?,music_singer=?,music_lyricist=?,music_composer=?," +
							"record=?,record_company=?,music_description=?,music_price=?,music_inventory=? where music_id=?");
			prepareStatement.setString(1, music_name);
			prepareStatement.setString(2, music_singer);
			prepareStatement.setString(3, music_lyricist);
			prepareStatement.setString(4, music_composer);
			prepareStatement.setString(5, record);
			prepareStatement.setString(6, record_company);
			prepareStatement.setString(7, music_description);
			prepareStatement.setDouble(8, music_price);
			prepareStatement.setString(9, music_inventory);
			prepareStatement.setString(10, music_id);
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	@Override
	public void editCategory(Category category) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("update category set category_name=?,category_desc=? where category_id=?");
			prepareStatement.setString(1, category.getCategory_name());
			prepareStatement.setString(2, category.getCategory_description());
			prepareStatement.setString(3, category.getCategory_id());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void delCategory(String category_id) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("delete from category where category_id=?");
			prepareStatement.setString(1, category_id);
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	@Override
	public List<User> findUsers() {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement("select * from user");
			ResultSet rs = prepareStatement.executeQuery();
			List<User> users = new ArrayList<User>();
			while (rs.next()) {
				User user = new User();
				user.setAddress(rs.getString("user_address"));
				user.setId(rs.getString("user_id"));
				user.setName(rs.getString("user_name"));
				user.setPassword(rs.getString("user_password"));
				user.setSex(rs.getString("user_sex"));
				user.setTel(rs.getString("user_tel"));
				user.setUsername(rs.getString("user_username"));
				users.add(user);
			}
			return users;
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException();
	}

	// 添加管理人员
	@Override
	public void addAdmin(Administrator admin) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("insert into administrator values(?,?,?,?,?)");
			prepareStatement.setString(1, admin.getUsername());
			prepareStatement.setString(2, admin.getPassword());
			prepareStatement.setString(3, admin.getName());
			prepareStatement.setString(4, admin.getSex());
			prepareStatement.setString(5, admin.getTel());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	// 音乐销售情况
	@Override
	public List<Music> sales() {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("select * from musicdb where music_heat>0 order by music_heat desc");
			ResultSet rs = prepareStatement.executeQuery();
			List<Music> musics = new ArrayList<Music>();
			while (rs.next()) {
				Music music = new Music();
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
				musics.add(music);
			}
			return musics;
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException();
	}

}
