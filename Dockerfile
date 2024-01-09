FROM archlinux:latest

# docker/ should have dwm, dwm.desktop
COPY ./docker/ /tmp/docker/
RUN echo 'Server = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch' > /etc/pacman.d/mirrorlist &&\
    pacman -Syu --noconfirm &&\
    pacman -S --noconfirm xorg &&\
    pacman -S --noconfirm tigervnc &&\
    mkdir -p /root/.vnc &&\
    echo "dwm" |vncpasswd -f > ~/.vnc/passwd &&\
    chmod 600 ~/.vnc/passwd &&\
    echo 'session=dwm' >> ~/.vnc/config &&\
    mkdir -p /usr/share/xsessions &&\
    cp /tmp/docker/dwm.desktop /usr/share/xsessions/dwm.desktop &&\
    cp /tmp/docker/dwm /bin/dwm &&\
    cp /tmp/docker/st /bin/st &&\
    cp -r /tmp/docker/scripts/ ~/.scripts/
CMD tail -f /dev/null
