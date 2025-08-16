package cn.xh.service.impl;

import java.util.List;
import java.util.UUID;

import cn.xh.dao.ClientDao;
import cn.xh.dao.impl.ClientDaoImpl;
import cn.xh.domain.Music;
import cn.xh.domain.Favorite;
import cn.xh.domain.User;
import cn.xh.service.ClientService;

public class ClientServiceImpl implements ClientService {

	private final ClientDao dao = new ClientDaoImpl();

	@Override
	public User login(String username, String password) {
		return dao.login(username, password);
	}

	@Override
	public boolean register(String username, String password, String name, String sex, String tel, String address) {
		User user = new User(UUID.randomUUID().toString(), username, password, name, sex, tel, address);
		return dao.register(user);
	}

	@Override
	public List<Music> getCategoryMusic(String cid) {
		return dao.getCategoryMusic(cid);
	}


	@Override
	public void personInformation(String username, String name, String sex, String tel, String address) {
		User user = new User(null, username, null, name, sex, tel, address);
		dao.personInformation(user);
	}

	@Override
	public void personPassword(String password, String username) {
		User user = new User(null, username, password, null, null, null, null);
		dao.personPassword(user);
	}

	@Override
	public List<Music> search(String search) {
		return dao.search(search);
	}

	@Override
	public Music findMusicById(String music_id) {
		return dao.findMusicById(music_id);
	}

	@Override
	public void addFavorite(String user_id, String music_id) {
		dao.addFavorite(UUID.randomUUID().toString(), user_id, music_id);
	}

	@Override
	public List<Favorite> findFavoriteByUserId(User user) {
		return null;
	}

	@Override
	public boolean findFavorite(String user_id, String music_id) {
		return dao.findFavorite(user_id, music_id);
	}

	@Override
	public void delFavorite(String music_id) {
		dao.delFavorite(music_id);
	}

}
