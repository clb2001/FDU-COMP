package cn.xh.dao;

import java.util.List;

import cn.xh.domain.Music;
import cn.xh.domain.User;

public interface ClientDao {

	User login(String username, String password);

	boolean register(User user);

	List<Music> getCategoryMusic(String cid);

	void personInformation(User user);

	void personPassword(User user);

	List<Music> search(String search);

	Music findMusicById(String music_id);

	void addFavorite(String string, String user_id, String music_id);

	boolean findFavorite(String user_id, String music_id);

	void delFavorite(String music_id);

}
