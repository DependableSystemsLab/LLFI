//jQuery to collapse the navbar on scroll
$(window).scroll(function() {
    if (!$(".navbar").offset()) return;
    if ($(".navbar").offset().top > 58) {
        $(".navbar").addClass("top-nav-collapse");
        $(".navbar").addClass("navbar-fixed-top");
    } else {
        $(".navbar").removeClass("top-nav-collapse");
        $(".navbar").removeClass("navbar-fixed-top");
    }

    if ($(".navbar").offset().top < 59) {
        $(".navbar").removeClass("navbar-fixed-top");
    }
});

//jQuery for page scrolling feature - requires jQuery Easing plugin
$(function() {
    $('a.page-scroll').bind('click', function(event) {
        var $anchor = $(this);
        $('html, body').stop().animate({
            scrollTop: $($anchor.attr('href')).offset().top
        }, 1500, 'easeInOutExpo');
        event.preventDefault();
    });
});
