package cn.xh.dao.impl;

import cn.xh.dao.ClientDao;
import cn.xh.domain.*;
import cn.xh.util.JDBCUtil;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
public class ClientDaoImpl implements ClientDao {
	// login
	@Override
	public User login(String username, String password) {
		User user = new User();
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement preparedStatement = connection
					.prepareStatement("select * from user where user_username=? and user_password=?");
			preparedStatement.setString(1, username);
			preparedStatement.setString(2, password);
			ResultSet executeQuery = preparedStatement.executeQuery();
			if (executeQuery.next()) {
				user.setUsername(executeQuery.getString("user_username"));
				user.setPassword(executeQuery.getString("user_password"));
				user.setName(executeQuery.getString("user_name"));
				user.setSex(executeQuery.getString("user_sex"));
				user.setTel(executeQuery.getString("user_tel"));
				user.setAddress(executeQuery.getString("user_address"));
				user.setId(executeQuery.getString("user_id"));
			} else {
			}
		} catch (Exception e) {
		}
		return user;
	}

	// register
	@Override
	public boolean register(User user) {
		Connection connection = JDBCUtil.getConnection();
		try {
			Statement statement = connection.createStatement();
			ResultSet resultSet = statement
					.executeQuery("select * from user where user_username='" + user.getUsername() + "'");
			if (resultSet.next() == true) {
				return true;
			} else {
				try {
					PreparedStatement preparedStatement = connection.prepareStatement(
							"insert into user (user_id,user_username,user_password,user_name,user_sex,user_tel,user_address) values(?,?,?,?,?,?,?)");
					preparedStatement.setString(1, user.getId());
					preparedStatement.setString(2, user.getUsername());
					preparedStatement.setString(3, user.getPassword());
					preparedStatement.setString(4, user.getName());
					preparedStatement.setString(5, user.getSex());
					preparedStatement.setString(6, user.getTel());
					preparedStatement.setString(7, user.getAddress());
					preparedStatement.executeUpdate();
				} catch (Exception e) {
					e.printStackTrace();
				}
				return false;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}

	// getCategoryMusic
	@Override
	public List<Music> getCategoryMusic(String cid) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement preparedStatement = null;

			if (cid==null){
				preparedStatement=  connection.prepareStatement(
                        "select * from musicdb");
            }else {
				preparedStatement =  connection.prepareStatement(
                        "select * from musicdb where music_category = (select category_id from category where category_id = '"+cid+"')");
            }

            ResultSet rs = preparedStatement.executeQuery();

			List<Music> list = new ArrayList<Music>();
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
				list.add(music);
			}
			return list;
		} catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException("runtime error!");
	}

	// findCategoryById
	// retrieve
	private Category findCategoryById(String music_category) {
		Category category = new Category();
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement preparedStatement = connection
					.prepareStatement("select * from category where category_id=?");
			preparedStatement.setString(1, music_category);
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

	// update
	@Override
	public void personInformation(User user) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement(
					"update user set user_name=?,user_sex=?,user_tel=?,user_address=? where user_username=?");
			prepareStatement.setString(1, user.getName());
			prepareStatement.setString(2, user.getSex());
			prepareStatement.setString(3, user.getTel());
			prepareStatement.setString(4, user.getAddress());
			prepareStatement.setString(5, user.getUsername());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// update
	@Override
	public void personPassword(User user) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("update user set user_password=? where user_username=?");
			prepareStatement.setString(1, user.getPassword());
			prepareStatement.setString(2, user.getUsername());
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// retrieve
	@Override
	public List<Music> search(String search) {
		List<Music> lists = new ArrayList<Music>();
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement preparedStatement = connection
					.prepareStatement("select * from musicdb where music_name like ?");
			preparedStatement.setString(1, "%" + search + "%");
			ResultSet rs = preparedStatement.executeQuery();
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
				lists.add(music);
			}
			return lists;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	// retrieve
	@Override
	public Music findMusicById(String music_id) {
		try {
			Music music = new Music();
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
			return music;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	// create
	// may have some problems
	@Override
	public void addFavorite(String favorite_id, String user_id, String music_id) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("insert into favorite (favorite_id,user_id,music_id) values (?,?,?)");
			prepareStatement.setString(1, favorite_id);
			prepareStatement.setString(2, user_id);
			prepareStatement.setString(3, music_id);
			prepareStatement.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}

	@Override
	public boolean findFavorite(String user_id, String music_id) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection
					.prepareStatement("select * from favorite where user_id=? and music_id=?");
			prepareStatement.setString(1, user_id);
			prepareStatement.setString(2, music_id);
			ResultSet rs = prepareStatement.executeQuery();
            return rs.next();
        } catch (Exception e) {
			e.printStackTrace();
		}
		throw new RuntimeException();
	}

	// delete
	@Override
	public void delFavorite(String music_id) {
		try {
			Connection connection = JDBCUtil.getConnection();
			PreparedStatement prepareStatement = connection.prepareStatement("delete from favorite where music_id=?");
			prepareStatement.setString(1, music_id);
			prepareStatement.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
