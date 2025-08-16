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
		<p style="font-size: 25px; margin-top: 20px; margin-left: 42px">添加音乐信息</p>
	</div>
	<hr
		style="height: 10px; border: none; border-top: 10px groove #bd7bde;" />
	<form style="margin-top: 30px; margin-left: 450px"
		action="<%=basePath%>/admin/ManagerServlet?op=addMusic" method="post"
		enctype="multipart/form-data">
		<div class="form-group">
			<label>音乐名称：</label> <input type="text" class="form-control"
				id="music_name" name="music_name" placeholder="音乐名称"
				style="width: 700px">
		</div>
		<div class="form-group">
			<label>演唱：</label> <input type="text" class="form-control"
				id="music_singer" name="music_singer" placeholder="演唱"
				style="width: 700px">
		</div>
		<div class="form-group">
			<label>作词：</label> <input type="text" class="form-control"
										id="music_lyricist" name="music_lyricist" placeholder="作词"
										style="width: 700px">
		</div>
		<div class="form-group">
			<label>作曲：</label> <input type="text" class="form-control"
										id="music_composer" name="music_composer" placeholder="作曲"
										style="width: 700px">
		</div>
		<div class="form-group">
			<label>所属专辑：</label> <input type="text" class="form-control"
										id="record" name="record" placeholder="所属专辑"
										style="width: 700px">
		</div>
		<div class="form-group">
			<label>唱片公司：</label> <input type="text" class="form-control"
											  id="record_company" name="record_company" placeholder="唱片公司"
											  style="width: 700px">
		</div>
		<div class="form-group">
			<label>音乐分类：</label> <select class="form-control" name="category_id"
				title="音乐分类" style="width: 700px">
				<option selected="selected">---所属分类---</option>
				<c:forEach items="${cs}" var="c">
					<option value="${c.category_id}">${c.category_name}</option>
				</c:forEach>
			</select>
		</div>
		<div class="form-group">
			<label>图片上传：</label> <input type="file"
				id="file" name="file">
		</div>
		<div class="form-group">
			<label>音乐简介：</label>
			<textarea class="form-control" rows="3" id="music_description"
				name="music_description" placeholder="音乐简介" style="width: 700px"></textarea>
		</div>
		<div class="form-group">
			<label>专辑单价：</label> <input type="text" class="form-control"
				id="music_price" name="music_price" placeholder="专辑单价/￥"
				style="width: 700px">
		</div>
		<div class="form-group">
			<label>专辑库存：</label> <input type="text" class="form-control"
				id="music_inventory" name="music_inventory" placeholder="专辑库存"
				style="width: 700px">
		</div>
		<br>
		<button type="submit" class="btn btn-default"
			onclick="window.location='manager/ManagerServlet?op=addMusic'">提交</button>
		<button type="button" class="btn btn-default" data-dismiss="modal"
			style="margin-left: 100px"
			onclick="window.location='managerIndex.jsp'">关闭</button>
	</form>
</body>
</html>