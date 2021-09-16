import DomHelper from "./dom-helper.js";
import Section from "./section.js";
import Snippet from "./snippet.js";
import DocId from "./documentid.js";
import VizzuView from './vizzu-view.js';

export default class Main
{
	constructor(snippetRegistry)
	{
		this.sections = new Map();
		this.snippets = new Map();

		this.discover();

		this.setupVizzu(snippetRegistry);

		this.lastSection = null;
		this.lastSubSection = null;

		this.contentView = document.getElementById('content-view');
		this.contentView.onscroll = event => this.scrolled(event);
	}

	setupVizzu(snippetRegistry)
	{
		this.vizzuView = new VizzuView('example-canvas');

		for (let [id, snippet] of snippetRegistry.snippets)
			this.vizzuView.register(id, snippet); 
	}

	discover()
	{

		let subtitles = document.getElementsByClassName('subtitle');
		for (let subtitle of subtitles) {
			const id = DomHelper.parseId(subtitle).id;
			this.sections.set(id, new Section(subtitle));
		}

		let submenus = document.getElementsByClassName('submenuitem');
		for (let submenu of submenus)
		{
			const id = DomHelper.parseId(submenu).id;
			let section = this.sections.get(id);
			if (section) section.setMenu(submenu);
		}

		let snippets = document.getElementsByClassName('snippet');
		for (let snippet of snippets)
		{
			const id = DomHelper.parseId(snippet).id;
			snippet.onclick = () => { this.activateSnippet(id); };
			this.snippets.set(id, new Snippet(snippet));
		}
	}

	scrolled(event)
	{
		const topSectionId = this.firstVisibleSubtitle();
		if (topSectionId != this.lastSection)
			this.activateSection(topSectionId)
	}

	activateSection(id)
	{
		if (this.lastSection !== null)
			this.getSection(this.lastSection).select(false);

		this.getSection(id).select(true);

		this.lastSection = id;
	}

	activateSnippet(id)
	{
		if (this.lastSubSection !== null)
		{
			let snippet = this.snippets.get(this.lastSubSection);
			if (snippet) snippet.select(false);
		}
		let snippet = this.snippets.get(id);
		if (snippet) snippet.select(true);

		this.vizzuView.step(id);

		this.lastSubSection = id;
	}

	getSection(id)
	{
		let sectionId = (new DocId(id)).getSectionId();
		return this.sections.get(sectionId);
	}

	firstVisibleSubtitle()
	{
		let last = '0.0';
		for (let [ id, section ] of this.sections)
		{
			if (this.isAboveViewCenter(section.element))
				return last;
			last = id;
		}

		return last;
	}

	isAboveViewCenter(child)
	{
		const childRect = child.getBoundingClientRect();
		const parentRect = this.contentView.getBoundingClientRect();
		return childRect.top > parentRect.top + parentRect.height/2;
	}

}
