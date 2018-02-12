FROM            ubuntu:16.04
MAINTAINER      Glider Labs
EXPOSE          25565
EXPOSE          22
RUN             apt-get update -y
RUN             apt-get install openjdk-8-jre -y
RUN             apt-get install openssh-server -y
RUN             apt-get install wget -y
ENTRYPOINT      start.sh
