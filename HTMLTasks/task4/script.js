galleryView = () => {
    const gallery = document.getElementById('gallery');
    gallery.classList.add('gallery-view');
    gallery.classList.remove('list-view');
}
listView = () => {
    const gallery = document.getElementById('gallery');
    gallery.classList.add('list-view');
    gallery.classList.remove('gallery-view');
}