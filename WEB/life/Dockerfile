FROM debian:buster-slim

# Setup user
RUN useradd www


COPY sources.list /

RUN mv /sources.list /etc/apt/sources.list

# Install system packeges
RUN apt-get update && apt-get install -y supervisor nginx lsb-release wget

# Add repos
RUN wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg
RUN echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/php.list

# Install PHP dependencies
RUN apt update && apt install -y php5.6-fpm

# Configure php-fpm and nginx
COPY config/fpm.conf /etc/php/5.6/fpm/php-fpm.conf
COPY config/supervisord.conf /etc/supervisord.conf
COPY config/nginx.conf /etc/nginx/nginx.conf

# Copy challenge files
COPY challenge /www

# Copy flag
COPY flag /

# Setup permissions
RUN chown -R www:www /www /var/lib/nginx

# Expose the port nginx is listening on
EXPOSE 80

# Generate random flag filename and start supervisord
COPY --chown=root entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

CMD ["/usr/bin/supervisord", "-c", "/etc/supervisord.conf"]
