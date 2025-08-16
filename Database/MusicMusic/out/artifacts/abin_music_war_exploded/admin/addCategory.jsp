<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
			 ;
%>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>添加音乐信息</title>
<link rel="stylesheet" href="<%=basePath%>/css/bootstrap.min.css" />
<link rel="stylesheet" href="<%=basePath%>/css/header.css" />
</head>
<body>
	<script type="text/javascript" src="js/jquery-2.0.3.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<div>
		<p style="font-size: 25px; margin-top: 20px; margin-left: 42px">添加音乐分类</p>
	</div>
	<hr
		style="height: 10px; border: none; border-top: 10px groove #bd7bde;" />
	<form style="margin-top: 30px; margin-left: 450px"
		action="<%=basePath%>/admin/ManagerServlet?op=addCategory"
		method="post">
		<div class="form-group">
			<label>音乐分类名称：</label> <input type="text" class="form-control"
				id="category_name" name="category_name" placeholder="音乐分类名称"
				style="width: 700px">
		</div>
		<div class="form-group">
			<label>音乐分类描述：</label>
			<textarea class="form-control" rows="3" id="category_description"
				name="category_description" placeholder="音乐分类描述" style="width: 700px"></textarea>
		</div>
		<br>
		<button type="submit" class="btn btn-default"
			onclick="window.location='manager/ManagerServlet?op=addCategory'">提交</button>
		<button type="button" class="btn btn-default" data-dismiss="modal"
			style="margin-left: 100px"
			onclick="window.location='managerIndex.jsp'">关闭</button>
	</form>
</body>
</html>