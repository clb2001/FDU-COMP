package cn.xh.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ResourceBundle;

public class JDBCUtil {
	/*
	��������Ǿ�̬�ģ���ζ�������ڸ�������ж�����Ҳ����˵�����۴������ٸ��������Ƕ�����ͬһ�� conn ������
	ͨ���ھ�̬��Ա�����б������ȫ�ֱ�����һ�����ڱ�����Ҫ�ڶ��������������֮�乲���״̬�����ݡ�
	����������У������̬�������ڱ������ݿ����ӣ��Ա������������ж�����ʹ��ͬһ�����Ӷ��󣬱������ظ��������Ӷ���Ŀ���������˳����Ч�ʡ�
	��Ҫע����ǣ���ʹ�þ�̬����ʱ��Ҫ�ر�С�ģ���Ϊ��̬�������������ںͳ������������һ���������ʹ�ò������ܻᵼ��һЩǱ�ڵ����⡣
	���磬�ڶ��̻߳�����ʹ�þ�̬����ʱ��Ҫ�����̰߳�ȫ���⡣
	 */
	static Connection conn = null;

	static {
		// ��ʼ��porperties�ļ�
		/*
		ResourceBundle bundle = ResourceBundle.getBundle("jdbcConfig"); ��һ�����ڶ�ȡ properties �ļ��� Java ��䡣
		���������У�ResourceBundle �� Java ��׼���е�һ���࣬���ڼ��غͽ��� properties �ļ������ṩ��һ��򵥵ķ���������ͨ��������ȡ��Ӧ��ֵ��
		getBundle(String baseName) ������ ResourceBundle ���ṩ��һ����̬���������ڼ���ָ�����Ƶ� properties �ļ���
		�������������ָ�����Ƶ� properties �ļ���������һ�� ResourceBundle ���󣬸ö�������� properties �ļ������еļ�ֵ�ԡ�
		����������У���� ResourceBundle.getBundle("jdbcConfig") ���������Ϊ "jdbcConfig.properties" �� properties �ļ���
		������һ�� ResourceBundle ���󣬿���ʹ����������ȡ�ļ��еļ�ֵ�ԡ�
		 */
		ResourceBundle bundle = ResourceBundle.getBundle("jdbcConfig");
		// driverManager = com.mysql.cj.jdbc.Driver
		// url = jdbc:mysql://localhost:3306/music_player?useSSL=false&serverTimezone=UTC
		// user=root
		// password=6514305aBc
		String dirver = bundle.getString("driverManager");
		String url = bundle.getString("url");
		String user = bundle.getString("user");
		String password = bundle.getString("password");
		// ע������
		try {
			/*
			�� Java �У���ͬ�����ݿ�ʹ�ò�ͬ�� JDBC �����������������ӺͲ�����
			��ˣ���ʹ�� JDBC �������ݿ�ʱ����Ҫ�ȼ������ݿ��Ӧ�� JDBC ���������࣬���ܹ�ʹ�ø����ݿ��ṩ�Ĺ��ܡ�
			���������У�Class �� Java ��׼���е�һ���࣬���ڱ�ʾһ�� Java �ࡣ
			forName(String className) �� Class ���ṩ��һ����̬���������ڼ��ز�����ָ���������ࡣ
			������ forName() ����ʱ��JVM ����Ҳ�����ָ�����Ƶ��࣬�����ظ����Ӧ�� Class ����
			��ʹ�� JDBC �������ݿ�ʱ��������Ҫ�ȼ������ݿ��Ӧ�� JDBC ���������ࡣ
			���磬���Ҫ���� MySQL ���ݿ⣬��Ҫʹ�� com.mysql.jdbc.Driver �����������ӺͲ�����
			 */
			Class.forName(dirver);
		} catch (Exception e) {
			e.printStackTrace();
		}

		try {
			/*
			DriverManager.getConnection(url, user, password) �� Java �����ڽ������ݿ����ӵ���䣬
			����佫����һ�� java.sql.Connection �������ڲ������ݿ⡣
			��ʹ�� JDBC �������ݿ�ʱ��������Ҫ��ȡһ�����ݿ����Ӷ��󣬸ö������������ݿ⽨�����Ӳ����в�����
			DriverManager ���� Java ��׼�����ṩ��һ���࣬���ڹ��� JDBC ��������
			���� getConnection() ������ DriverManager ���ṩ��һ����̬���������ڴ������ݿ����ӡ�
			���������У�url �����������ַ���������ָ��Ҫ���ӵ����ݿ��λ�ú����Ƶ���Ϣ��
			user ������ password �����ֱ����������ݿ�����Ҫ���û��������롣
			������ getConnection() ����ʱ��JVM ��ʹ��ע�ᵽ DriverManager �е� JDBC ������������ָ�������ݿ⽨�����ӣ�
			������һ�� Connection ���󣬸ö������ڲ������ݿ⡣
			���ص� Connection ���󱣴�����Ϊ conn �ı����У��Թ����������ݿ����ʹ�á�
			 */
			conn = DriverManager.getConnection(url, user, password);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static Connection getConnection() {
		return conn;
	}
	
	public static void release(ResultSet set, Statement stmt, Connection connection) throws SQLException {
		if (set != null) {
			set.close();
		}
		if (stmt != null) {
			stmt.close();
		}
		if (connection != null) {
			connection.close();
		}
	}
}
