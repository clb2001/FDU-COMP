package cn.xh.service;

import java.util.List;

import cn.xh.domain.Administrator;
import cn.xh.domain.Music;
import cn.xh.domain.Category;
import cn.xh.domain.User;

public interface ManagerService {

	Administrator login(String username, String password);

	void managerInformation(String username, String name, String sex, String tel);

	void managerPassword(String username, String password);

	List<Category> findAllCategory();

	Category findCategoryById(String category_id);

	void addMusic(Music music);

	void addCategory(Category category);

	List<Music> getCategoryMusic(String cid);

	Music findMusicById(String music_id);

	void delMusic(String music_id);

	void editMusic(String music_id, String music_name, String music_singer, String music_lyricist,
				   String music_composer, String record, String record_company, String music_description,
				   double music_price, String music_inventory);

	void editCategory(Category category);

	void delCategory(String category_id);

	List<User> findUsers();

	void addAdmin(Administrator admin);

	List<Music> sales();

}
