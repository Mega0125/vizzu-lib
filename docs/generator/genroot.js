"use strict";

const fs = require('fs');
const jsdom = require('jsdom');
const marked = require('marked');
const { JSDOM } = jsdom;

class Generator
{
	constructor()
	{
		this.loadHTML().then(dom => {
			this.generate(dom);
			this.saveHTML(dom);
		});
	}

	loadHTML()
	{
		return JSDOM.fromFile("index.root.in.html");
	}

	generate(dom)
	{
		const readmeFile = '../../README.md';

		marked.setOptions({
			highlight: function(code, lang) {
			  const hljs = require('highlight.js');
			  const language = hljs.getLanguage(lang) ? lang : 'plaintext';
			  return hljs.highlight(code, { language }).value;
			},
		});

		let defaultRender = new marked.Renderer();

		marked.use({
			renderer: {
				link: function (href, title, string) {
					if (!href.startsWith('http') && !href.startsWith('mailto'))
						href = 'https://github.com/vizzuhq/vizzu-lib/blob/main/'+href;
					return defaultRender.link(href, title, string);
				}
			}
		});
	
		let markedContent = fs.readFileSync(readmeFile, 'utf-8');
		let html = marked(markedContent);

		let content = dom.window.document.getElementById('content');
		content.innerHTML = html;
	}

	saveHTML(dom)
	{
		fs.writeFile('../../index.html', dom.serialize(), console.error);
	}
}

let run = new Generator();
