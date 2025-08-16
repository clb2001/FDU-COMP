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
<link rel="stylesheet" href="<%=basePath%>/css/bootstrap.min.css" />
<link rel="stylesheet" href="<%=basePath%>/css/header.css" />
<title>专辑销售情况</title>
</head>
<body>
	<script type="text/javascript" src="js/jquery-2.0.3.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<div>
		<p style="font-size: 25px; margin-top: 20px; margin-left: 42px">专辑销售情况</p>
	</div>
	<hr
		style="height: 10px; border: none; border-top: 10px groove #bd7bde;" />
	<div>
		<table class="table table-bordered table-hover"
			style="margin-left: 16px; width: 1560px">
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
			</tr>
			<c:forEach items="${sales}" var="s" varStatus="vs">
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
				</tr>
			</c:forEach>
		</table>
	</div>
</body>
</html>