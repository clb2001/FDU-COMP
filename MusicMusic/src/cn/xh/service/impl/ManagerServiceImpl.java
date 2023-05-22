package cn.xh.service.impl;

import cn.xh.dao.ManagerDao;
import cn.xh.dao.impl.ManagerDaoImpl;
import cn.xh.domain.Administrator;
import cn.xh.domain.Music;
import cn.xh.domain.Category;
import cn.xh.domain.User;
import cn.xh.service.ManagerService;

import java.util.List;
import java.util.UUID;

public class ManagerServiceImpl implements ManagerService {
	private final ManagerDao dao = new ManagerDaoImpl();

	@Override
	public Administrator login(String username, String password) {
		return dao.login(username, password);
	}

	@Override
	public void managerInformation(String username, String name, String sex, String tel) {
		Administrator admin = new Administrator(username, null, name, sex, tel);
		dao.managerInformation(admin);
	}

	@Override
	public void managerPassword(String username, String password) {
		Administrator admin = new Administrator(username, password, null, null, null);
		dao.managerPassword(admin);
	}

	@Override
	public List<Category> findAllCategory() {
		return dao.findAllCategory();
	}

	@Override
	public Category findCategoryById(String category_id) {
		return dao.findCategoryById(category_id);
	}

	@Override
	public void addMusic(Music music) {
		music.setMusic_id(UUID.randomUUID().toString());
		dao.addMusic(music);

	}

	@Override
	public void addCategory(Category category) {
		category.setCategory_id(UUID.randomUUID().toString());
		dao.addCategory(category);
	}

	@Override
	public List<Music> getCategoryMusic(String cid) {
		return dao.getCategoryMusic(cid);
	}

	@Override
	public Music findMusicById(String music_id) {
		return dao.findMusicById(music_id);
	}

	@Override
	public void delMusic(String music_id) {
		dao.delMusic(music_id);
	}

	@Override
	public void editMusic(String music_id, String music_name, String music_singer, String music_lyricist,
						  String music_composer, String record, String record_company, String music_description,
						  double music_price, String music_inventory) {
		dao.editMusic(music_id, music_name, music_singer, music_lyricist, music_composer, record,
				record_company, music_description, music_price, music_inventory);
	}

	@Override
	public void editCategory(Category category) {
		dao.editCategory(category);
	}

	@Override
	public void delCategory(String category_id) {
		dao.delCategory(category_id);
	}

	@Override
	public List<User> findUsers() {
		return dao.findUsers();
	}

	@Override
	public void addAdmin(Administrator admin) {
		dao.addAdmin(admin);
	}

	@Override
	public List<Music> sales() {
		return dao.sales();
	}

}
