FROM ghcr.io/europeanroverchallenge/erc-remote-image-base:latest

# Install additional packages
RUN apt-get update && apt-get -y upgrade && apt-get -y install \
  tmux \
  vim \
  python-rosdep \
  python-catkin-tools \
  ros-melodic-ar-track-alvar \
  ros-melodic-depthimage-to-laserscan \
  ros-melodic-robot-localization \
  ros-melodic-robot-pose-ekf \
  ros-melodic-message-filters \
  ros-melodic-image-view \
  ros-melodic-map-server \
  ros-melodic-move-base \
  ros-melodic-pointcloud-to-laserscan \
  ros-melodic-teb-local-planner \
  ros-melodic-costmap-2d \
  ros-melodic-pcl-ros \
  && rm -rf /var/lib/apt/lists/*

# Copy packages and build the workspace
WORKDIR /catkin_ws
COPY src ./src
RUN apt-get update \
  && rosdep update \
  && rosdep install --from-paths src -iy \
  && rm -rf /var/lib/apt/lists/*
RUN catkin config --extend /opt/ros/melodic && catkin build --no-status

# Automatically source the workspace when starting a bash session
RUN echo "source /catkin_ws/devel/setup.bash" >> /etc/bash.bashrc

# Install start script
COPY ./start.sh /

CMD ["/start.sh"]