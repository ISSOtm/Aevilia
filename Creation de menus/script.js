var nbElements = 1,
	dernierElement = 0,
	nomsOptions =  ['chaine',
					'pause',
					'fonction',
					'sauter',
					'appeler',
					'menu',
					'attendre',
					'effacer',
					'options',
					'objet',
					'warp',
					'octet',
					'editionFlag',
					'entrerTexte'],
	externs = '', commandes = '';

function ajouterElement() {
	$('#elements > li').first().clone().appendTo('#elements');
	dernierElement++;
	
	var elementAjoute = $('#elements > li').last().children('div');
	elementAjoute.children('.panel-heading').children('.numeroElement').text(dernierElement);
	elementAjoute.children('.panel-body').children('form').children('.choixOption').children('select').children('option').first().click();
	
	nbElements++;
}

function retirerElement(IDelement) {
	if(nbElements != 1) {
		nbElements--;
		$('#elements > li').slice(IDelement - dernierElement + nbElements).first().remove();
	}
}

function afficherOption(el) {
	var formulaire = $(el)/* option */.parent()/* select */.parent()/* form-group */.parent()/* form */;
	formulaire.children('.option').addClass('hidden');
	formulaire.children('.option-' + nomsOptions[parseInt(el.value)]).removeClass('hidden');
}


function clonerOptions(el) {
	var nbOptions = parseInt($(el).parent().children('.nbOptions').val()), commandesOptions = $(el).parent().children('.commandesOptions'), chainesOptions = $(el).parent().children('.chainesOptions');
	if(isNaN(el.value)) {
		nbOptions = 1;
		el.value = '1';
	}
	
	commandesOptions.children('.commandeOptions').slice(1).remove();
	chainesOptions.children('.chaineOptions').slice(1).remove();
	commandesOptions.children('.commandeOptions').children('input').val('');
	chainesOptions.children('.chaineOptions').children('input').val('');
	for(var i = 1; i < nbOptions; i++) {
		commandesOptions.children('.commandeOptions').first().clone().appendTo(commandesOptions).children('label').children('small').children('.numCommandeOptions').text(i);
		chainesOptions.children('.chaineOptions').first().clone().appendTo(chainesOptions).children('label').children('small').children('.numChaineOptions').text(i);
	}
}

function genererSimple(el) {
	return el.children('input').val() + ', ';
}
function genererSauter(el) {
	return el.children('.nomCondition').val() + ', &commande' + $('#namespace').val() + el.children('.commandeReussite').val() + ', &commande' + $('#namespace').val() + el.children('.commandeEchec').val();
}
function genererAppeler(el) {
	return el.children('.nomCondition').val() + ', &commande' + $('#namespace').val() + el.children('.commandeReussite').val() + ', &commande' + $('#namespace').val() + el.children('.commandeEchec').val() + ', ';
}
function genererMenu(el) {
	return '&amp;' + genererSimple(el);
}
function genererRien(el) {
	return '';
}
function genererOptions(el) {
	var str = '', pref = $('#namespace').val() + el.parent().parent().parent().children('.panel-heading').children('.numeroElement').text(), nbOptions = el.children('.nbOptions').val();
	el.children('.commandesOptions').children('.commandeOptions').each(function(i, e) {
		if(i != 0) {
			str += ', '
		}
		str += $(e).children('input').val();
	});
	commandes += '<br />Commande* commandesOptionsCommande' + pref + '[' + nbOptions + '] = {' + str + '};';
	str = '"';
	el.children('.chainesOptions').children('.chaineOptions').each(function(i, e) {
		if(i != 0) {
			str += '", "'
		}
		str += $(e).children('input').val();
	});
	commandes += '<br />wchar_t texteOptionsCommande' + pref + '[' + nbOptions + '][LONG_NOM_OPTIONS] = {' + str + '"};';
	return 'commandesOptionsCommande' + pref + ', chainesOptionsCommande' + pref + ', ' + nbOptions + ', ';
}
function genererDouble(el) {
	return el.children('input').first().val() + ', ' + el.children('input').last().val() + ', ';
}
function genererOctet(el) {
	return '&amp;' + el.children('input').first().val() + ', ' + el.children('input').last().val() + ', ' + el.children('select').children(':selected').val() + ', ';
}
function genererCode() {
	externs = '', commandes = '';
	var prefixe = $('#namespace').val(),
	nomsMacros =   ['CHAINE',
					'PAUSE',
					'FONCTION',
					'SAUTER_COND',
					'APPELER_COND',
					'AJOUTER_MENU',
					'ATTENDRE',
					'EFFACER',
					'OPTIONS',
					'OBJET',
					'WARP',
					'OCTET',
					'FLAG',
					'ENTREE'],
	fonctions =    [genererSimple,
					genererSimple,
					genererSimple,
					genererSauter,
					genererAppeler,
					genererMenu,
					genererRien,
					genererRien,
					genererOptions,
					genererDouble,
					genererDouble,
					genererOctet,
					genererDouble,
					genererSimple];
	$('.panel').each(function(i, el) {
		var formulaire = $(el).children('.panel-body').children('form'), selectionne = formulaire.children('.choixOption').children('select').children(':selected').val(), pref = prefixe + $(el).children('.panel-heading').children('.numeroElement').text(), prochaine = formulaire.children('.choixSuivante').children('input').val(), prochCommande = '';
		externs += 'extern Commande commande' + pref + ';<br />';
		prochCommande = '<br />Commande commande' + pref + ' = CMD_' + nomsMacros[selectionne] + '(' + fonctions[selectionne](formulaire.children('.option:not(.hidden)')) + ((selectionne != 3) ? (prochaine != -1) ? '&amp;commande' + prefixe + prochaine : 'NULL' : '') + ');';
		commandes += prochCommande;
	});
	$('#sortie').html(externs + commandes);
}


$('document').ready(function(){
	$('option:selected').first().click();
	$('.nbOptions').val('1');
});

