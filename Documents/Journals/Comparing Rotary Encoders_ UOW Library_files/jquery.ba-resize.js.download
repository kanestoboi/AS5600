/*
 * jQuery resize event - v1.1 - 3/14/2010
 * http://benalman.com/projects/jquery-resize-plugin/
 * 
 * Copyright (c) 2010 "Cowboy" Ben Alman
 * Dual licensed under the MIT and GPL licenses.
 * http://benalman.com/about/license/
 */
(function($,k,j){var a=$([]),b=$.resize=$.extend($.resize,{}),i,g="setTimeout",f="resize",d=f+"-special-event",e="delay",h="throttleWindow";b[e]=250;b[h]=true;$.event.special[f]={setup:function(){if(!b[h]&&this[g]){return false;}var l=$(this);a=a.add(l);$.data(this,d,{w:l.width(),h:l.height()});if(a.length===1){c();}},teardown:function(){if(!b[h]&&this[g]){return false;}var l=$(this);a=a.not(l);l.removeData(d);if(!a.length){clearTimeout(i);}},add:function(l){if(!b[h]&&this[g]){return false;}var n;function m(p,s,r){var q=$(this),o=$.data(this,d);if(!o){o=$.data(this,d,{});}o.w=s!==j?s:q.width();o.h=r!==j?r:q.height();n.apply(this,arguments);}if($.isFunction(l)){n=l;return m;}else{n=l.handler;l.handler=m;}}};function c(){i=k[g](function(){a.each(function(){var m=$(this),o=m.width(),n=m.height(),l=$.data(this,d);if(o!==l.w||n!==l.h){m.trigger(f,[l.w=o,l.h=n]);}});c();},b[e]);}})(jQuery,this);