FROM            ubuntu:16.04
MAINTAINER      Glider Labs
EXPOSE          25565
WORKDIR         ~/
ADD             ./ ./
ADD             ./mods ./mods
RUN             apt-get update -y
RUN             apt-get install openjdk-8-jre -y
RUN             apt-get install wget -y
RUN             wget http://s3.amazonaws.com/Minecraft.Download/launcher/Minecraft.jar
RUN             chmod +x Minecraft.jar
ENTRYPOINT      /bin/bash
