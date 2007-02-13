<!-- created by Tammy Fox tfox@redhat.com for the Fedora Project -->
<!-- License: GPL -->
<!-- Copyright 2003 Tammy Fox, Red Hat, Inc. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				xmlns:exsl="http://exslt.org/common"
				version="1.0"
				exclude-result-prefixes="exsl">

<xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets/xhtml/docbook.xsl"/>
<xsl:import href="redhat.xsl"/>
<xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets/xhtml/chunk-common.xsl"/>
<xsl:include href="/usr/share/sgml/docbook/xsl-stylesheets/xhtml/manifest.xsl"/>

<xsl:include href="/usr/share/sgml/docbook/xsl-stylesheets/xhtml/chunk-code.xsl"/>

<xsl:include href="html-common.xsl"/>

<!-- TOC -->
<xsl:param name="toc.section.depth">2</xsl:param>
<xsl:param name="section.autolabel" select="1"/>
<xsl:param name="section.label.includes.component.label" select="1"></xsl:param>

<xsl:param name="generate.legalnotice.link" select="1"></xsl:param>

<xsl:param name="generate.toc">
book toc
article toc
chapter toc
qandadiv toc
qandaset toc
sect1 nop
sect2 nop
sect3 nop
sect4 nop
sect5 nop
section toc
</xsl:param>

<!-- TOC -->
<!-- unselect all child nodes of sections when building chapter TOC -->
<!-- Effectively allowing only level 1 sections to be selected -->
<xsl:template match="section" mode="toc">
		<xsl:param name="toc-context" select="."/>
		<xsl:choose>
				<xsl:when test="local-name($toc-context) = 'chapter'">
						<xsl:call-template name="subtoc">
								<xsl:with-param name="toc-context" select="$toc-context"/>
								<xsl:with-param name="nodes" select="foo"/>
						</xsl:call-template>
				</xsl:when>
				<xsl:otherwise>
						<xsl:call-template name="subtoc">
								<xsl:with-param name="toc-context" select="$toc-context"/>
								<xsl:with-param name="nodes"
											select="section|sect1|glossary|bibliography|index
														 |bridgehead[$bridgehead.in.toc != 0]"/>
						</xsl:call-template>
				</xsl:otherwise>
		</xsl:choose>
</xsl:template>

<xsl:template match="revhistory">
	<xsl:variable name="numcols">
		<xsl:choose>
			<xsl:when test="//authorinitials">3</xsl:when>
			<xsl:otherwise>2</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:variable name="doctitle" select="//title"/>

	<div class="{name(.)}">
		<table border="1" width="100%" summary="Revision history - {$doctitle}">
			<tr>
				<th align="left" valign="top" colspan="{$numcols}">
					<b>
						<xsl:call-template name="gentext">
							<xsl:with-param name="key" select="'RevHistory'"/>
						</xsl:call-template>
					</b>
				</th>
			</tr>
			<xsl:apply-templates>
				<xsl:with-param name="numcols" select="$numcols"/>
			</xsl:apply-templates>
		</table>
	</div>
</xsl:template>

<xsl:template match="revhistory/revision">	
	<xsl:param name="numcols" select="'3'"/>
	<xsl:variable name="revnumber" select=".//revnumber"/>
	<xsl:variable name="revdate"	 select=".//date"/>
	<xsl:variable name="revauthor" select=".//authorinitials"/>
	<xsl:variable name="revremark" select=".//revremark|.//revdescription"/>
	<tr>
		<td align="left">
			<xsl:if test="$revnumber">
				<xsl:call-template name="gentext">
					<xsl:with-param name="key" select="'Revision'"/>
				</xsl:call-template>
				<xsl:call-template name="gentext.space"/>
				<xsl:apply-templates select="$revnumber[1]"/>
			</xsl:if>
		</td>
		<td align="left">
			<xsl:apply-templates select="$revdate[1]"/>
		</td>
		<xsl:choose>
			<xsl:when test="$revauthor">
				<td align="left">
					<xsl:apply-templates select="$revauthor[1]"/>
				</td>
			</xsl:when>
			<xsl:when test="$numcols &gt; 2">
				<td>&#160;</td>
			</xsl:when>
			<xsl:otherwise></xsl:otherwise>
		</xsl:choose>
	</tr>
	<xsl:if test="$revremark">
		<tr>
			<td align="left" colspan="{$numcols}">
				<xsl:apply-templates select="$revremark[1]"/>
			</td>
		</tr>
	</xsl:if>
</xsl:template>

<xsl:template match="revhistory" mode="titlepage.mode">
	<xsl:variable name="id">revhistory</xsl:variable>
	<xsl:variable name="filename">
		<xsl:call-template name="make-relative-filename">
			<xsl:with-param name="base.dir" select="$base.dir"/>
			<xsl:with-param name="base.name" select="concat('rv-',$id,$html.ext)"/>
		</xsl:call-template>
	</xsl:variable>

	<a href="{concat('rv-',$id,$html.ext)}">Revision History</a>

	<xsl:call-template name="write.chunk">
		<xsl:with-param name="filename" select="$filename"/>
		<xsl:with-param name="quiet" select="$chunk.quietly"/>
		<xsl:with-param name="content">
			<xsl:call-template name="user.preroot"/>
			<html>
				<head>
					<xsl:call-template name="system.head.content"/>
					<xsl:call-template name="head.content"/>
					<xsl:call-template name="user.head.content"/>
				</head>
				<body>
					<xsl:call-template name="body.attributes"/>
					<div class="{local-name(.)}">
						<xsl:apply-templates select="."/>
					</div>
				</body>
			</html>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>


<!-- Navigation
<xsl:param name="navig.graphics" select="1"></xsl:param>
<xsl:param name="navig.graphics.extension" select="'.png'"></xsl:param>
<xsl:param name="navig.graphics.path">nav-images/</xsl:param>
<xsl:param name="navig.showtitles">1</xsl:param>
-->


<xsl:param name="suppress.navigation" select="1"></xsl:param>
<xsl:param name="suppress.header.navigation" select="1"></xsl:param>
<xsl:param name="suppress.footer.navigation" select="1"></xsl:param>
<xsl:param name="header.rule" select="0"></xsl:param>
<xsl:param name="footer.rule" select="0"></xsl:param>

<!-- BUGBUG TODO 

	There is a bug where inserting elements in to the body level
	of xhtml will add xmlns="" to the tag. This is invalid xhtml.
	To overcome this I added:
		xmlns="http://www.w3.org/1999/xhtml"
	to the outer most tag. This gets stripped by the parser, resulting
	in valid xhtml ... go figure.
-->
<xsl:template name="header.navigation">
	<xsl:param name="prev" select="/foo"/>
	<xsl:param name="next" select="/foo"/>
	<xsl:param name="nav.context"/>

	<xsl:variable name="home" select="/*[1]"/>
	<xsl:variable name="up" select="parent::*"/>

	<xsl:variable name="row1" select="$navig.showtitles != 0"/>
	<xsl:variable name="row2" select="count($prev) &gt; 0 or (count($up) &gt; 0 and generate-id($up) != generate-id($home) and $navig.showtitles != 0) or count($next) &gt; 0"/>

	<xsl:if test="$suppress.navigation != '0' and $suppress.header.navigation != '0'">
		<xsl:if test="$row1 or $row2">
			<xsl:if test="$row1">
				<p xmlns="http://www.w3.org/1999/xhtml">
					<xsl:attribute name="id">
						<xsl:text>title</xsl:text>
					</xsl:attribute>
					<a>
						<xsl:attribute name="href">
							<xsl:text>docsbase</xsl:text>
						</xsl:attribute>
						<strong>
							<xsl:apply-templates select="." mode="object.title.markup"/>
						</strong>
					</a>
				</p>
			</xsl:if>
			<xsl:if test="$row2">
				<ul class="docnav" xmlns="http://www.w3.org/1999/xhtml">
					<li class="previous">
						<xsl:if test="count($prev)&gt;0">
							<a accesskey="p">
								<xsl:attribute name="href">
									<xsl:call-template name="href.target">
										<xsl:with-param name="object" select="$prev"/>
									</xsl:call-template>
								</xsl:attribute>
								<strong>
								<xsl:call-template name="navig.content">
									<xsl:with-param name="direction" select="'prev'"/>
								</xsl:call-template>
							</strong></a>
						</xsl:if>
					</li>
					<li class="next">
						<xsl:if test="count($next)&gt;0">
							<a accesskey="n">
								<xsl:attribute name="href">
									<xsl:call-template name="href.target">
										<xsl:with-param name="object" select="$next"/>
									</xsl:call-template>
								</xsl:attribute>
								<strong>
								<xsl:call-template name="navig.content">
									<xsl:with-param name="direction" select="'next'"/>
								</xsl:call-template>
							</strong></a>
						</xsl:if>
					</li>
				</ul>
			</xsl:if>
		</xsl:if>
		<xsl:if test="$header.rule != 0">
			<hr/>
		</xsl:if>
	</xsl:if>
</xsl:template>

<xsl:template name="footer.navigation">
	<xsl:param name="prev" select="/foo"/>
	<xsl:param name="next" select="/foo"/>
	<xsl:param name="nav.context"/>
	<xsl:param name="title-limit" select="'50'"/>

	<xsl:variable name="home" select="/*[1]"/>
	<xsl:variable name="up" select="parent::*"/>

	<xsl:variable name="row1" select="count($prev) &gt; 0 or count($up) &gt; 0 or count($next) &gt; 0"/>
	<xsl:variable name="row2" select="($prev and $navig.showtitles != 0) or (generate-id($home) != generate-id(.) or $nav.context = 'toc') or ($chunk.tocs.and.lots != 0 and $nav.context != 'toc') or ($next and $navig.showtitles != 0)"/>

	<xsl:if test="$suppress.navigation != '0' and $suppress.footer.navigation != '0'">
		<xsl:if test="$footer.rule != 0">
			<hr/>
		</xsl:if>

		<xsl:if test="$row1 or $row2">
			<ul class="docnav" xmlns="http://www.w3.org/1999/xhtml">
				<xsl:if test="$row1">
					<li class="previous">
						<xsl:if test="count($prev) &gt; 0">
							<a accesskey="p">
								<xsl:attribute name="href">
									<xsl:call-template name="href.target">
										<xsl:with-param name="object" select="$prev"/>
									</xsl:call-template>
								</xsl:attribute>
								<strong>
									<xsl:call-template name="navig.content">
										<xsl:with-param name="direction" select="'prev'"/>
									</xsl:call-template>
								</strong>
								<xsl:variable name="text">
									<xsl:apply-templates select="$prev" mode="object.title.markup"/>
								</xsl:variable>
								<xsl:choose>
									<xsl:when test="string-length($text) &gt; $title-limit">
										<xsl:value-of select="concat(substring($text, 0, $title-limit), '...')"/>
									</xsl:when>
									<xsl:otherwise>
										<xsl:value-of select="$text"/>
									</xsl:otherwise>
								</xsl:choose>
							</a>
						</xsl:if>
					</li>
					<xsl:if test="count($up) &gt; 0">
						<li class="up">
							<a accesskey="u">
								<xsl:attribute name="href"><xsl:text>#</xsl:text></xsl:attribute>
								<strong>
								<xsl:call-template name="navig.content">
									<xsl:with-param name="direction" select="'up'"/>
								</xsl:call-template>
							</strong></a>
						</li>
					</xsl:if>
					<xsl:if test="$home != . or $nav.context = 'toc'">
						<li class="home">
							<a accesskey="h">
								<xsl:attribute name="href">
									<xsl:call-template name="href.target">
										<xsl:with-param name="object" select="$home"/>
									</xsl:call-template>
								</xsl:attribute>
								<strong>
								<xsl:call-template name="navig.content">
									<xsl:with-param name="direction" select="'home'"/>
								</xsl:call-template>
							</strong></a>
						</li>
					</xsl:if>
					<xsl:if test="count($next)&gt;0">
						<li class="next">
							<a accesskey="n">
								<xsl:attribute name="href">
									<xsl:call-template name="href.target">
										<xsl:with-param name="object" select="$next"/>
									</xsl:call-template>
								</xsl:attribute>
								<strong>
								<xsl:call-template name="navig.content">
									<xsl:with-param name="direction" select="'next'"/>
								</xsl:call-template>
							</strong>
								<xsl:variable name="text">
									<xsl:apply-templates select="$next" mode="object.title.markup"/>
								</xsl:variable>
								<xsl:choose>
									<xsl:when test="string-length($text) &gt; $title-limit">
										<xsl:value-of select="concat(substring($text, 0, $title-limit),'...')"/>
									</xsl:when>
									<xsl:otherwise>
										<xsl:value-of select="$text"/>
									</xsl:otherwise>
								</xsl:choose>
<!--							<xsl:apply-templates select="$next" mode="object.title.markup"/> -->
						</a>
						</li>
					</xsl:if>
				</xsl:if>
			</ul>
		</xsl:if>
	</xsl:if>
</xsl:template>

<xsl:template name="graphical.admonition">
	<xsl:variable name="admon.type">
		<xsl:choose>
			<xsl:when test="local-name(.)='note'">Note</xsl:when>
			<xsl:when test="local-name(.)='warning'">Warning</xsl:when>
			<xsl:when test="local-name(.)='caution'">Caution</xsl:when>
			<xsl:when test="local-name(.)='tip'">Tip</xsl:when>
			<xsl:when test="local-name(.)='important'">Important</xsl:when>
			<xsl:otherwise>Note</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<div xmlns="http://www.w3.org/1999/xhtml" class="{name(.)}">
		<xsl:attribute name="summary">
			<xsl:value-of select="$admon.type"/>
			<xsl:if test="title">
				<xsl:text>: </xsl:text>
				<xsl:value-of select="title"/>
			</xsl:if>
			</xsl:attribute>
			<xsl:call-template name="anchor"/>
			<xsl:if test="$admon.textlabel != 0 or title">
				<h2>
				<xsl:apply-templates select="." mode="object.title.markup"/>
				</h2>
			</xsl:if>
		<xsl:apply-templates/>
	</div>
</xsl:template>


</xsl:stylesheet>
