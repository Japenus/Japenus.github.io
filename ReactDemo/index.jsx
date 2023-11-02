require('./app/lib/common.css');
import React from 'react';
import ReactDOM from 'react-dom';
import Search from './app/components/search.jsx';
import Header from './app/components/header.jsx';
import Like from './app/components/like.jsx';
ReactDOM.render(
	<div>
		<Search />
		<Header source="http://localhost:3000/data/swiper" />
		<Like source="http://localhost:3000/data/like" />
	</div>,
	document.querySelector("#myApp")
);
