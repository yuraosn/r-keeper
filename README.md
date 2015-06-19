 Задача модуля 

	commerce_rkeeper – модуль для информационной системы, суши-бара, будет содержит в себе 5 подмодулей, для реализации всего функционала.

	card_rkeeper – модуль расширяющий подобный функционал модуля commerce_coupon. Для реализации возможности привязать к заказам и к своему личному кабинету свою карту гостя, которая выдается в заведении. Модуль будет высчитывать процент или сумму (в зависимости от карты) скидки к заказу. Можно будет использовать 2 вида карт, как скидка под определенный процент, так и скидка на определенную сумму;

	prepay_rkeeper – модуль, дающий возможность оплачивать не полную стоимость заказа, а делать предоплаты, на сумму не ниже и не выше установленной в настройках сайта. Данная информация сохраняется в заказе и в customer, будет отображается в личном кабинете пользователя;

	sms_rkeeper – оповещает посетителей сайта которые сделали заказ, по смс, отправляя им номер заказа, на их мобильный телефон. Производит синхронизацию между сайтом «Токио» и сайтом СМС-центр, которые предоставляют услугу отправку СМС сообщений посредством установки на сайт их API. СМС отправляется посетителям: при удачном завершении заказа, если заказ со стороны заведения был изменен, при балансе менее 5 рублей оповещение администратору;

	tables_rkeeper – отображает в реальном времени занятые и свободные столики, вставляет в заказ дополнительную страницу, на которой отображается описание, план двух залов и свободные столики, из которых можно выбрать подходящий и забронировать его. Дополняет в модуль customer информацию о выбранных данных, которые будут после завершения заказа отображаться в личном кабинете пользователя;

	sync_rkeeper – самый главный модуль, он является сердцем перечисленных модулей, которые обращаются к нему, за необходимыми данными. Модуль соединяет R-keeper и сайт, производя синхронизацию по определенным запросам. Каждый модуль обращаясь к sync_rkeeper получает для себя отдельные данные, согласно его запросу. Собирает все данные воедино, от всех модулей и отправляет их на сервер R-keeper для сохранения заказа. Модуль содержит в себе административную панель в которую заполняются данные сервера для обмена. Предоставляет панель для автоматического переноса товаров с R-keeper на сайт.
