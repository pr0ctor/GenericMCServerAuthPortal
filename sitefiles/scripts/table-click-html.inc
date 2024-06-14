<script>
$(document).ready(function() {
    var mouse_is_inside = false;
    $(".datatableTable #<?php echo $sourceDataTableId; ?>").on("click", "tbody td", function(event) {

        $("#side-panel").hide();
        $('input[name="ApprovalType"]').prop('checked', false);

        const clicked = $(this).closest("tr");
        const rowId = clicked.find("td:nth-child(1)").text();
        const discordName = clicked.find("td:nth-child(2)").text();
        const minecraftName = clicked.find("td:nth-child(3)").text();

        $(".side-panel #applicationid").val(rowId);
        $(".side-panel #discordName").text(discordName);
        $(".side-panel #minecraftName").text(minecraftName);

        clicked.siblings().attr("id", "");
        clicked.attr("id", "selected-table-row");

        $(".side-panel").css({
            top: event.pageY,
            left: event.pageX
        }).show();
    });

    $('.side-panel').hover(function(){ 
        mouse_is_inside=true; 
    }, function(){ 
        mouse_is_inside=false; 
    });

    $('.datatableTable #<?php echo $sourceDataTableId; ?>').hover(function(){ 
        mouse_is_inside=true; 
    }, function(){ 
        mouse_is_inside=false; 
    });

    $("body").mouseup(function(){ 
        if(! mouse_is_inside) {
            $('.side-panel').hide();
            $("#selected-table-row").attr("id", "");
            $('input[name="ApprovalType"]').prop('checked', false);
        } 
    });
});
</script>

<div class="side-panel" align="center">
    <form method="post" action="operations.html">
        <div id="rowId"><input type="hidden" name="recordid" id="applicationid"><input type="hidden" value="<?php echo $operationType; ?>" name="operation"></div>
        <div><p><strong>Member</strong></p></div>
        <div><p id="discordName"></p></div>
        <div><p id="minecraftName"></p></div>
        <hr>
        <?php 
            if($operationType == "approve-application") {

        ?>
        <div class="mb-3 form-check"><input type="radio" name="ApprovalType" class="form-check-input" id="approvalTypeApproved" value="Approved"><label class="form-check-label" for="approvalTypeApproved">Approved</label></div>
        <div class="mb-3 form-check"><input type="radio" name="ApprovalType" class="form-check-input" id="approvalTypeDenied" value="Denied"><label class="form-check-label" for="approvalTypeDenied">Denied</label></div>
        <div class="mb-3"><input type="submit" title="Submit" class="btn btn-primary"></div>
        <?php 
            }
            
            if($operationType == "ban-member") {
                
        ?>
        <div class="mb-3"><label for="reason-text">Reason</label><textarea name="reason" id="reason-text" class="form-control" rows="3"></textarea></div>
        <div class="mb-3"><input type="submit" value="Ban Member" class="btn btn-danger"></div>
        <?php
            }
        ?>
    </form>
</div>