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
<title>音乐信息维护</title>
<link rel="stylesheet" href="<%=basePath%>/css/bootstrap.min.css" />
</head>
<body>
	<script type="text/javascript" src="js/jquery-2.0.3.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<!-- 音乐导航条 -->
	<nav class="navbar navbar-default" style="margin-bottom: 0px;">
	<div class="container-fluid">
		<div class="navbar-header">
			<button type="button" class="navbar-toggle collapsed"
				data-toggle="collapse" data-target="#bs-example-navbar-collapse-1"
				aria-expanded="false">
				<span class="sr-only">Toggle navigation</span> <span
					class="icon-bar"></span> <span class="icon-bar"></span> <span
					class="icon-bar"></span>
			</button>
			<a class="navbar-brand" href="<%=basePath%>/admin/ManagerServlet?op=category">音乐分类</a>
		</div>
		<div class="collapse navbar-collapse"
			id="bs-example-navbar-collapse-1">
			<ul class="nav navbar-nav">
				<c:forEach items="${categoryList}" var="c">
					<li><a href="<%=basePath%>/admin/ManagerServlet?op=category&cid=${c.category_id}">${c.category_name}</a></li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				</c:forEach>
			</ul>
			<!-- 搜索框 -->
			<div style="float: right; margin-right: 7px">
				<form class="navbar-form navbar-left"
					action="<%=basePath%>/admin/ManagerServlet?op=search"
					method="post">
					<div class="form-group">
						<input type="text" name="search" class="form-control"
							placeholder="搜索/音乐名称">
					</div>
					<button type="submit" class="btn btn-default">搜索</button>
				</form>
			</div>
		</div>
	</div>
	</nav>
	<c:if test="${!empty musics}">
		<table class="table table-bordered table-hover" style="width: 100%">
			<tr>
				<th style="width: 100px">音乐编号</th>
				<th style="width: 100px">专辑图片</th>
				<th style="width: 200px">音乐名称</th>
				<th style="width: 200px">音乐类型</th>
				<th style="width: 200px">演唱</th>
				<th style="width: 200px">作词</th>
				<th style="width: 200px">作曲</th>
				<th style="width: 200px">所属专辑</th>
				<th style="width: 300px">唱片公司</th>
				<th style="width: 200px">专辑价格</th>
				<th style="width: 200px">销量</th>
				<th style="width: 200px">操作</th>
			</tr>
			<c:forEach items="${musics}" var="s" varStatus="vs">
				<tr class="active">
					<td>${vs.index+1}</td>
					<td><img style="width: 80px; height: 100px"
						src="${pageContext.request.contextPath}/img/${s.path}/${s.filename}" />
					</td>
					<td>${s.music_name}</td>
					<td>${s.category.category_name}</td>
					<td>${s.music_singer}</td>
					<td>${s.music_lyricist}</td>
					<td>${s.music_composer}</td>
					<td>${s.record}</td>
					<td>${s.record_company}</td>
					<td><span style="color: rgb(198, 46, 45); font-weight: bold">￥${s.music_price}</span></td>
					<td style="color: red"><strong>${s.music_heat}</strong></td>
					<td><a
						href="<%=basePath%>/admin/ManagerServlet?op=editMusicUI&music_id=${s.music_id}">编辑</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
						<a
						href="<%=basePath%>/admin/ManagerServlet?op=delMusic&music_id=${s.music_id}"
						onclick="if(confirm('确定删除'+'${s.music_name}'+'?')===false) return false;">删除</a>
				</tr>
			</c:forEach>
		</table>
	</c:if>
</body>
</html>