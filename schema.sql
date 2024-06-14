-- drop table ips;
drop table bans;
drop table whitelist;
drop table approvals;
drop table applications;
drop table members;
drop table servers;
drop table application_type;
drop table mcaccounts;


create table application_type(
    application_type varchar(50),
    primary key(application_type)
);

create table servers(
    server_type varchar(50),
    primary key(server_type)
);

create table mcaccounts(
    id bigint auto_increment unique,
    name varchar(100),
    uuid char(36),
    primary key(id)
);

create table members(
    id bigint auto_increment unique,
    discord_id varchar(100),
    discord_name varchar(250),
    mcaccount bigint,
    primary key(id),
    foreign key(mcaccount) references mcaccounts(id)
);

create table applications(
    id bigint auto_increment unique,
    member bigint,
    server_type varchar(50),
    application_type varchar(50),
    application_date timestamp default current_timestamp,
    primary key(id),
    foreign key(member) references members(id),
    foreign key(server_type) references servers(server_type),
    foreign key(application_type) references application_type(application_type)
);

create table approvals(
    id bigint auto_increment unique,
    application_id bigint,
    approver bigint,
    approval_date timestamp default current_timestamp,
    primary key(id),
    foreign key(application_id) references applications(id),
    foreign key(approver) references members(id)
);

create table whitelist(
    id bigint auto_increment unique,
    member bigint,
    server_type varchar(50),
    mcaccount bigint,
    primary key(id),
    foreign key(member) references members(id),
    foreign key(server_type) references servers(server_type),
    foreign key(mcaccount) references mcaccounts(id)
);

create table bans(
    id bigint auto_increment unique,
    member bigint,
    mcaccount bigint,
    reason text,
    bandate timestamp default current_timestamp,
    primary key(id),
    foreign key(member) references members(id),
    foreign key(mcaccount) references mcaccounts(id)
);

-- create table ips(
--     id bigint auto_increment unique,
--     member bigint,
--     ip varchar(50),
--     primary key(id),
--     foreign key(member) references members(id)
-- );

insert into application_type values("Pending");
insert into application_type values("Approved");
insert into application_type values("Denied");

insert into servers values("Vanilla");
insert into servers values("Modded");
insert into servers values("Both");